Public Class ImageConverter

    Public Sub New()
    End Sub

    Public Shared Function ImageToIPicture(ByVal Image As System.Drawing.Image) As stdole.StdPicture
        ImageToIPicture = Microsoft.VisualBasic.Compatibility.VB6.ImageToIPicture(Image)
    End Function


    Public Shared Function IPictureToImage(ByVal Image As stdole.StdPicture) As System.Drawing.Image
        IPictureToImage = Microsoft.VisualBasic.Compatibility.VB6.IPictureToImage(Image)
    End Function
End Class
