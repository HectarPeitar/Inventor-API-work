using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;

namespace AssemblyTree
{
	/// <summary>
	/// AssemblyTree Form.
	/// </summary>
	public class frmAssemblyTree : System.Windows.Forms.Form
	{
		internal System.Windows.Forms.Button cmdClose;
		internal System.Windows.Forms.OpenFileDialog OpenFileDialog;
		internal System.Windows.Forms.Button cmdRefreshTree;
		private System.ComponentModel.IContainer components;
		private System.Windows.Forms.ImageList imageList;
		private System.Windows.Forms.TreeView treList;
		internal System.Windows.Forms.TextBox txtFileName;
		internal System.Windows.Forms.Button cmdBrowse;
		private System.Windows.Forms.GroupBox grpBoxAssemblyFile;

		private Inventor.ApprenticeServerComponent objapprenticeServerApp = new Inventor.ApprenticeServerComponentClass();

		public frmAssemblyTree()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if (components != null) 
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
		}

		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.components = new System.ComponentModel.Container();
			System.Resources.ResourceManager resources = new System.Resources.ResourceManager(typeof(frmAssemblyTree));
			this.cmdClose = new System.Windows.Forms.Button();
			this.OpenFileDialog = new System.Windows.Forms.OpenFileDialog();
			this.cmdRefreshTree = new System.Windows.Forms.Button();
			this.imageList = new System.Windows.Forms.ImageList(this.components);
			this.treList = new System.Windows.Forms.TreeView();
			this.grpBoxAssemblyFile = new System.Windows.Forms.GroupBox();
			this.txtFileName = new System.Windows.Forms.TextBox();
			this.cmdBrowse = new System.Windows.Forms.Button();
			this.grpBoxAssemblyFile.SuspendLayout();
			this.SuspendLayout();
			// 
			// cmdClose
			// 
			this.cmdClose.Location = new System.Drawing.Point(200, 296);
			this.cmdClose.Name = "cmdClose";
			this.cmdClose.Size = new System.Drawing.Size(88, 32);
			this.cmdClose.TabIndex = 22;
			this.cmdClose.Text = "Close";
			this.cmdClose.Click += new System.EventHandler(this.cmdClose_Click);
			// 
			// cmdRefreshTree
			// 
			this.cmdRefreshTree.Location = new System.Drawing.Point(72, 296);
			this.cmdRefreshTree.Name = "cmdRefreshTree";
			this.cmdRefreshTree.Size = new System.Drawing.Size(88, 32);
			this.cmdRefreshTree.TabIndex = 21;
			this.cmdRefreshTree.Text = "Refresh Tree";
			this.cmdRefreshTree.Click += new System.EventHandler(this.cmdRefreshTree_Click);
			// 
			// imageList
			// 
			this.imageList.ImageSize = new System.Drawing.Size(16, 16);
			this.imageList.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList.ImageStream")));
			this.imageList.TransparentColor = System.Drawing.Color.Transparent;
			// 
			// treList
			// 
			this.treList.ImageList = this.imageList;
			this.treList.Location = new System.Drawing.Point(16, 64);
			this.treList.Name = "treList";
			this.treList.Size = new System.Drawing.Size(320, 224);
			this.treList.TabIndex = 23;
			// 
			// grpBoxAssemblyFile
			// 
			this.grpBoxAssemblyFile.Controls.Add(this.txtFileName);
			this.grpBoxAssemblyFile.Controls.Add(this.cmdBrowse);
			this.grpBoxAssemblyFile.Location = new System.Drawing.Point(16, 8);
			this.grpBoxAssemblyFile.Name = "grpBoxAssemblyFile";
			this.grpBoxAssemblyFile.Size = new System.Drawing.Size(320, 48);
			this.grpBoxAssemblyFile.TabIndex = 24;
			this.grpBoxAssemblyFile.TabStop = false;
			this.grpBoxAssemblyFile.Text = "Assembly File:";
			// 
			// txtFileName
			// 
			this.txtFileName.AutoSize = false;
			this.txtFileName.Location = new System.Drawing.Point(8, 16);
			this.txtFileName.Name = "txtFileName";
			this.txtFileName.Size = new System.Drawing.Size(232, 24);
			this.txtFileName.TabIndex = 20;
			this.txtFileName.Text = "";
			// 
			// cmdBrowse
			// 
			this.cmdBrowse.Location = new System.Drawing.Point(248, 16);
			this.cmdBrowse.Name = "cmdBrowse";
			this.cmdBrowse.Size = new System.Drawing.Size(64, 24);
			this.cmdBrowse.TabIndex = 21;
			this.cmdBrowse.Text = "Browse...";
			this.cmdBrowse.Click += new System.EventHandler(this.cmdBrowse_Click);
			// 
			// frmAssemblyTree
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(352, 334);
			this.Controls.Add(this.grpBoxAssemblyFile);
			this.Controls.Add(this.treList);
			this.Controls.Add(this.cmdRefreshTree);
			this.Controls.Add(this.cmdClose);
			this.Name = "frmAssemblyTree";
			this.Text = "Assembly Tree";
			this.Load += new System.EventHandler(this.frmAssemblyTree_Load);
			this.grpBoxAssemblyFile.ResumeLayout(false);
			this.ResumeLayout(false);

		}
		#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new frmAssemblyTree());
		}

		private void cmdBrowse_Click(object sender, System.EventArgs e)
		{
			//setup parameters for the open dialog
			OpenFileDialog openFileDlg = new OpenFileDialog();
			openFileDlg.InitialDirectory = objapprenticeServerApp.FileLocations.Workspace;
			openFileDlg.Title = "Select Assembly file";
			openFileDlg.DefaultExt = ".iam";
			openFileDlg.Filter = "Inventor Assembly File (*.iam) | *.iam";
			openFileDlg.ShowDialog();
	
			//write the filename to the text box
			txtFileName.Text = openFileDlg.FileName;

			//check to see if a filename is not empty and call the BuildTree function
			if (txtFileName.Text != "") 
			{
				BuildTree();
			}
		}

		private void cmdRefreshTree_Click(object sender, System.EventArgs e)
		{
			//check to see if a filename was specified and call the BuildTree function
			if (txtFileName.Text != "") 
			{
				BuildTree();
			}
		}

		//traverse the assembly structure and build the occurrence tree.
		private void BuildTree()
		{
			try
			{
				//suppress re-painting the tree view until all nodes have been created
				treList.BeginUpdate();

				//clear the tree contents
				treList.Nodes.Clear();

                Inventor.ApprenticeServerDocument objapprenticeServerDocument;
	
				//open the specified file
				objapprenticeServerDocument = objapprenticeServerApp.Open(txtFileName.Text);

				if (objapprenticeServerDocument == null)
				{
					MessageBox.Show("Unable to open the specified file", "Invalid File", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
					return;
				}			

				//build a node for the top level assembly
				TreeNode objTopNode = new TreeNode(objapprenticeServerDocument.DisplayName, 0, 0);
				treList.Nodes.Add(objTopNode);

				//call the recursive function to iterate through the assembly tree
				GetComponents(objapprenticeServerDocument.ComponentDefinition.Occurrences, objTopNode);

				//expand the node representing the top level assembly
				objTopNode.Expand();

				//re-paint the tree view 
				treList.EndUpdate();

			}
			catch(Exception) 
			{
				MessageBox.Show("Unable to open and get the assembly heirarchy of the specified file", "Invalid File", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
			}
		}
	
		//get the components from the Occurrences collection and add it to the tree
		private void GetComponents(Inventor.ComponentOccurrences inCollection, TreeNode objparentNode)
		{

			//iterate through the components in the current collection
			IEnumerator objoccsEnumerator = inCollection.GetEnumerator();

            Inventor.ComponentOccurrence objcompOccurrence;
			while(objoccsEnumerator.MoveNext() == true) 
			{
                objcompOccurrence = (Inventor.ComponentOccurrence)objoccsEnumerator.Current;
				
				int ImageType;

				//determine if the current component is an assembly or part
                if (objcompOccurrence.DefinitionDocumentType == Inventor.DocumentTypeEnum.kAssemblyDocumentObject)
					ImageType = 0;
				else
					ImageType = 1;

				TreeNode objcurrentNode = new TreeNode(objcompOccurrence.Name, ImageType, ImageType);
				objparentNode.Nodes.Add(objcurrentNode);

				//recursively call this function for the suboccurrences of the current component
                GetComponents((Inventor.ComponentOccurrences)objcompOccurrence.SubOccurrences, objcurrentNode);

				objcurrentNode.Expand();

			}
	
		}

		private void cmdClose_Click(object sender, System.EventArgs e)
		{
			Application.Exit();
		}

		private void frmAssemblyTree_Load(object sender, System.EventArgs e)
		{
		
		}
	}
}
