using System;
using Inventor;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace DefineEdge
{
	public class DefineEdge
	{
		private Inventor.Application m_oApplication;
		private Inventor.Document    m_oDoc;

		public DefineEdge()
		{
		}

		private bool ConnectInventor()
		{	
			try
			{
				try
				{
					// Get active inventor object
					m_oApplication = MarshalCore.GetActiveObject( "Inventor.Application" ) as Inventor.Application;
				}
				catch( COMException )
				{
					MessageBox.Show( "DefineEdge : Inventor must be running." );
					return false;
				}

				// Make sure that at least one document is opened
				m_oDoc = m_oApplication.ActiveDocument;
				if( m_oDoc==null )
				{
					MessageBox.Show( "DefineEdge : An document must be active." );
					return false; 
				}				
			}
			catch( Exception e )
			{
				MessageBox.Show( e.Message );
				return false;
			}

			return true;
		}

		public void Execute()
		{
			if( !ConnectInventor() )
				return;

			// Set a reference to the select set.
			SelectSet oSelectSet = m_oApplication.ActiveDocument.SelectSet;
			
			// Check to see that a single item is in the select set.
			if( oSelectSet.Count == 1 )
			{
				// Check to see that an edge is selected.
				if( oSelectSet[1] is Edge )
				{
					// Set a reference to the edge in the select set.
					Edge oEdge = oSelectSet[1] as Edge;

					// Clear the select set.
					oSelectSet.Clear();
					
					// Check to make sure the selected edge is a circle or arc.
					if( (oEdge.CurveType == CurveTypeEnum.kCircleCurve) || (oEdge.CurveType == CurveTypeEnum.kCircularArcCurve) )
					{
						// Check to see if the attribute set has already been assigned.
						AttributeSetsEnumerator oAttribSets = m_oApplication.ActiveDocument.AttributeManager.FindAttributeSets( "AutoBolts", "*", Type.Missing  );
						if( oAttribSets.Count == 0 )
						{							
							// Add the attribute set to the selected edge.
							AttributeSet oAttribSet = oEdge.AttributeSets.Add( "AutoBolts", true );
							oAttribSet.Add( "AutoBolts", ValueTypeEnum.kIntegerType, 1 );
						}
						else
						{
							// An existing attribute set already exists so highlight the edge
							// that has the attribute.
							HighlightSet oHighlightSet = m_oApplication.ActiveDocument.HighlightSets.Add();
							AttributeSets oTempAttribSets = oAttribSets[1].Parent as AttributeSets;							
							oHighlightSet.AddItem( oTempAttribSets.Parent );
							if( MessageBox.Show( "The attribute is already assigned to the highlighted edge. \r\n Do you want to overwrite it?", "DefineEdge", MessageBoxButtons.YesNo )==DialogResult.OK )
							{
								// Clear the highlight set.
								oHighlightSet.Clear();

								// Remove the attribute set from the current item.
								oAttribSets[1].Delete();

								// Add the attribute set to the selected edge.
								oEdge.AttributeSets.Add( "AutoBolts", true );
							}
							else
							{
								oHighlightSet.Clear();
								return;
							}
						}
					}
					else
					{
						MessageBox.Show( "A circular edge must be selected." );
					}
				}
				else
				{
					MessageBox.Show( "A circular edge must be selected." );
				}
			}
			else
			{
				MessageBox.Show( "A circular edge must be selected." );
			}
		}

		public static void Main()
		{
			DefineEdge DefEdge = new DefineEdge();

			try
			{
				DefEdge.Execute();
			}
			catch( Exception )
			{
			}

		}
	}
}
