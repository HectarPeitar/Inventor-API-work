/*
	Copyright © 1998 by Autodesk, Inc.


	DESCRIPTION

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!!! This file is provided for backwards compatibility for existing clients only.
!!! New clients should probably consider using the more robust CComSafeArray wrapper provided in ATL instead.
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	This file contains utility functions and classes for dealing with the
	SAFEARRAY data type.


	HISTORY

	KK  :  10/11/99  :  Creation
*/

#ifndef _AUTODESK_INVENTOR_SAFEARRAYUTIL_
#define _AUTODESK_INVENTOR_SAFEARRAYUTIL_

#include <oleauto.h>
#include <vector>
#include <assert.h>


// Template utility class to convert to/from arrays of the template type to/from a safearray.
// Typical usage (without error handling) could be:
//
//	Server usage:
//
//	HRESULT Func(/*[in]*/ SAFEARRAY* psa, /*[out]*/ SAFEARRAY** ppsa)
//	{
//		...
//		CSafeArray<double, VT_R8> in(psa);
//		long length = 0;
//		in.Length(length);
//		std::vector<double> data(length);
//		for (long i = 0;i < length;++i)
//			data[i] = in[i] * 2;
//
//		CSafeArray<double, VT_R8> out(data.size(), data.begin());
//		*ppsa = out.Detach();
//		...
//	}
//
//	Or:
//
//	HRESULT Func2(/*[in]*/ SAFEARRAY* psa, /*[out]*/ SAFEARRAY** ppsa)
//	{
//		...
//		CSafeArray<double, VT_R8> in(psa);
//		long length = 0;
//		in.Length(length);
//		double* pData = in.DataBase();
//		std::vector<double> data(length);
//		for (long i = 0;i < length;++i)
//			data[i] = pData[i] * 2;
//
//		CSafeArray<double, VT_R8> out(ppsa)
//		return out.SetData(data.size(), data.begin());
//	}
//
//	Client usage:
//
//	// calling IServer::GetArray([out]SafeArray(double)* ppsa)
//	void Client(IServer* pServer)
//	{
//		CSafeArray<double, VT_R8> data;
//		pServer->GetArray(&data);
//		// Access data, no cleanup required
//	}
//
// Usage note: When used with VT_DISPATCH, VT_UNKNOWN, and VT_BSTR types,
// accessor methods such as SetData and operator[] use SafeArrayAccessData.
// When setting data, ownership of the BSTR or interface is assumed, so a
// client must copy the BSTR or AddRef the interface if this is not desired.
// When querying the data, direct access to the internal SAFEARRAY's data
// is handed out, so if the BSTR or interface is to be kept by, or further
// handed out of the client, a copy or AddRef must be performed by the client.

template<class T, VARENUM TYPE>
class CSafeArray
{
public:
	explicit CSafeArray() :
		m_psa(nullptr), m_owner(true), m_accessBase(nullptr)
	{}
	~CSafeArray()
	{
		Release();
	}

	// Initialize a CSafeArray from an existing safearray,
	// optionally destroying the safearray on instance destruction.
	explicit CSafeArray(SAFEARRAY* psa, bool ownit = false) :
		m_psa(psa), m_owner(ownit), m_accessBase(nullptr)
	{
			assert(psa ? (SafeArrayGetDim(psa) == 1) : true);
	}

	// Initialze a CSafeArray from a c-style data array.
	explicit CSafeArray(ULONG dataLength, const T* pData) :
		m_psa(nullptr), m_owner(true), m_accessBase(nullptr)
	{
		m_data.assign(pData, pData + dataLength);
	}

	// Initialize a CSafeArray from an existing safearray and set the
	// input pointer to a newly created safearray if it does not already
	// point to an existing safearray.	This constructor is intended for
	// output arguments which may or may not point to existing safearrays.
	// Specifically, in the case where a variable in VB is dimmed 'Dim var() as XXX',
	// an [in, out] SAFEARRAY(double) argument will point to void.
	explicit CSafeArray(SAFEARRAY** ppsa) :
		m_psa(ppsa ? *ppsa : nullptr), m_owner(false), m_accessBase(nullptr)
	{
		if (ppsa && !*ppsa)
			*ppsa = GetSafeArray();

		// GetSafeArray will construct a safearray and assume we must own it.
		// Reset the owning flag to false to indicate that ppsa owns it.
		m_owner = false;
	}

	CSafeArray(const CSafeArray& rhs) :
		m_psa(NULL), m_owner(false), m_accessBase(NULL)
	{operator=(rhs);}

	CSafeArray& operator=(CSafeArray& rhs)
	{
		if (&m_psa != &rhs.m_psa)
		{
			HRESULT hr = S_OK;
			Release();
			SAFEARRAY* psa = rhs.GetSafeArray();
			if (psa)
			{
				hr = SafeArrayCopy(psa, &m_psa);
				if (SUCCEEDED(hr))
					m_owner = true;
			}
			else
				hr = E_UNEXPECTED;
			assert(SUCCEEDED(hr));
		}
		return *this;
	}

	bool operator!()
	{return !GetSafeArray();}

	const SAFEARRAY* SafeArray() const
	{
		SAFEARRAY* psa = GetSafeArray();
		if (m_accessBase && psa)
		{
			HRESULT hr = SafeArrayUnaccessData(psa);
			assert(SUCCEEDED(hr)); UNREFERENCED_PARAMETER(hr);
			m_accessBase = NULL;
		}
		return psa;
	}

	SAFEARRAY* Detach()
	{
		SAFEARRAY* psa = GetSafeArray();
		if (m_accessBase && psa)
		{
			HRESULT hr = SafeArrayUnaccessData(psa);
			assert(SUCCEEDED(hr)); UNREFERENCED_PARAMETER(hr);
			m_accessBase = nullptr;
		}
		m_psa = nullptr;
		return psa;
	}

	void Release()
	{
		if (m_accessBase && m_psa)
		{
			HRESULT hr = SafeArrayUnaccessData(m_psa);
			assert(SUCCEEDED(hr)); UNREFERENCED_PARAMETER(hr);
		}
		if (m_psa && m_owner)
			SafeArrayDestroy(m_psa);
	m_psa = nullptr;
	m_owner = true;
	m_accessBase = nullptr;
	}

	T& operator[](ULONG i)
	{
		if (!m_accessBase)
		{
			HRESULT hr = AccessData();
			assert(SUCCEEDED(hr)); UNREFERENCED_PARAMETER(hr);
		}
		return m_accessBase[i];
	}

	const T& operator[](ULONG i) const
	{
		if (!m_accessBase)
		{
			HRESULT hr = AccessData();
			assert(SUCCEEDED(hr)); UNREFERENCED_PARAMETER(hr);
		}
		return m_accessBase[i];
	}

	T* DataBase()
	{
		if (!m_accessBase)
		{
			HRESULT hr = AccessData();
			assert(SUCCEEDED(hr)); UNREFERENCED_PARAMETER(hr);
		}
		return m_accessBase;
	}

	SAFEARRAY** operator&()
	{
		// Directly accessing the address of the internal SAFEARRAY is assumed
		// to only be done with the intent to use as an out argument in a call
		// and should therefore only be done when it is NULL or leaking will occur.
		// If this is not the intent, access the m_psa member directly.
		assert(!m_psa);
		return &m_psa;
	}

	HRESULT AccessData()
	{
		HRESULT hr = S_OK;
		if (!m_accessBase)
		{
			SAFEARRAY* psa = GetSafeArray();
			if (psa && !m_accessBase)
				hr = SafeArrayAccessData(psa, reinterpret_cast<void**>(&m_accessBase));
		}
		return hr;
	}

	HRESULT Length(long& length)
	{
		length = 0;
		HRESULT hr = E_FAIL;
		SAFEARRAY* psa = GetSafeArray();
		if (psa)
		{
			long lbound, ubound;
			hr = SafeArrayGetLBound(psa, 1, &lbound);
			if (SUCCEEDED(hr))
			{
				hr = SafeArrayGetUBound(psa, 1, &ubound);
				if (SUCCEEDED(hr))
					length = ubound - lbound + 1;
			}
		}
		
		return hr;
	}

	// Set the contents of the safearray to the c-style array specified.
	// If the safearray is not large enough to contain the data and redim
	// is true, it will attempt to redimension the safearray to fit the data.
	// In the case where a variable in VB is dimensioned with an explicit size,
	// e.g. 'Dim var(0 to 2) as XXX' as opposed to dynamicly e.g. 'Dim var() as XXX',
	// redimensioning will fail because VB will hold a lock on the data.
	HRESULT SetData(ULONG dataLength, const T* pData, bool redim = true)
	{
		long length;
		HRESULT hr = Length(length);
		bool redimmed = false;
		if (SUCCEEDED(hr))
		{
			if (length < (long)dataLength)
			{
				// Length ensured m_psa is up to date.
				if (!redim || SafeArrayGetDim(m_psa) != 1)
					hr = E_INVALIDARG;
				else
				{
					redimmed = true;
					SAFEARRAYBOUND bound;
					bound.cElements = dataLength;
					hr = SafeArrayGetLBound(m_psa, 1, &bound.lLbound);
					if (SUCCEEDED(hr))
					{
						// release any locks
						if (m_accessBase)
						{
							hr = SafeArrayUnaccessData(m_psa);
							m_accessBase = nullptr;
						}
						if (SUCCEEDED(hr))
							hr = SafeArrayRedim(m_psa, &bound);
					}
				}
			}
			T* pBase = nullptr;
			if (SUCCEEDED(hr) && (pBase = DataBase()) != nullptr)
				for (ULONG i = 0;i < dataLength;++i)
					pBase[i] = pData[i];
		}

		return SUCCEEDED(hr) ? (redimmed ? S_FALSE : S_OK) : hr;
	}

	// Set the contents of the safearray to the contents specified by the iterator.
	// If the safearray is not large enough to contain the data and redim
	// is true, it will attempt to redimension the safearray to fit the data.
	// In the case where a variable in VB is dimensioned with an explicit size,
	// e.g. 'Dim var(0 to 2) as XXX' as opposed to dynamicly e.g. 'Dim var() as XXX',
	// redimensioning will fail because VB will hold a lock on the data.
	template<class IT>
	HRESULT SetDataIterator(ULONG dataLength, IT it, bool redim = true)
	{
		long length;
		HRESULT hr = Length(length);
		bool redimmed = false;
		if (SUCCEEDED(hr))
		{
			if (length < (int)dataLength)
			{
				// Length ensured m_psa is up to date.
				if (!redim || SafeArrayGetDim(m_psa) != 1)
					hr = E_INVALIDARG;
				else
				{
					redimmed = true;
					SAFEARRAYBOUND bound;
					bound.cElements = dataLength;
					hr = SafeArrayGetLBound(m_psa, 1, &bound.lLbound);
					if (SUCCEEDED(hr))
					{
						// release any locks
						if (m_accessBase)
						{
							hr = SafeArrayUnaccessData(m_psa);
							m_accessBase = nullptr;
						}
						if (SUCCEEDED(hr))
							hr = SafeArrayRedim(m_psa, &bound);
					}
				}
			}
			T* pBase = nullptr;
			if (SUCCEEDED(hr) && ((pBase = DataBase()) != nullptr))
				for (ULONG i = 0;i < dataLength;++it,++i)
					pBase[i] = *it;
		}

		return SUCCEEDED(hr) ? (redimmed ? S_FALSE : S_OK) : hr;
	}

private:
	SAFEARRAY* GetSafeArray();

public:
	SAFEARRAY* m_psa{ nullptr };
	bool m_owner{false};
	using DataType = std::vector<T>;
	DataType m_data;

private:
	T* m_accessBase{ nullptr };
};


template <class T, VARENUM TYPE>
inline SAFEARRAY* CSafeArray<T, TYPE>::GetSafeArray()
{
	if (!m_psa)
	{
		SAFEARRAYBOUND bound;
		bound.lLbound = 0;
		bound.cElements = static_cast<ULONG> (!m_data.empty() ? m_data.size() : 1);
		m_psa = SafeArrayCreate(TYPE, 1, &bound);
		if (m_psa)
		{
			HRESULT hr = SafeArrayAccessData(m_psa, reinterpret_cast<void**>(&m_accessBase));
			if (SUCCEEDED(hr))
				for (ULONG i = 0;i < m_data.size();++i)
					m_accessBase[i] = m_data[i];
			m_owner = true;
		}
	}
	assert(m_psa);
	return m_psa;
}


using CSafeArrayDouble = CSafeArray<double, VT_R8>;
using CSafeArrayLong = CSafeArray<long, VT_I4>;
using CSafeArrayBSTR = CSafeArray<BSTR, VT_BSTR>;
using CSafeArrayFloat = CSafeArray<float,VT_R4>;

#endif // _SAFEARRAYUTIL_
