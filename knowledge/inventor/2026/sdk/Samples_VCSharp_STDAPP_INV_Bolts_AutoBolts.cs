using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;


namespace AutoBolts
{
	using Inventor;
	using System.Runtime.InteropServices;

	/// <summary>
	/// Summary description for Form1.
	/// </summary>
	public class Form1 : System.Windows.Forms.Form
	{
		private System.Windows.Forms.Button PlaceBolts;
		private System.Windows.Forms.Button Cancel;
		private System.Windows.Forms.Button Browser;
		private System.Windows.Forms.TextBox LibPath;
		private System.Windows.Forms.ImageList imageList;
		private System.Windows.Forms.TreeView treeView;
		private System.ComponentModel.IContainer components;
		private BoltPlacer m_BoltPlacer;

		public Form1()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
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
			System.Resources.ResourceManager resources = new System.Resources.ResourceManager(typeof(Form1));
			this.treeView = new System.Windows.Forms.TreeView();
			this.imageList = new System.Windows.Forms.ImageList(this.components);
			this.PlaceBolts = new System.Windows.Forms.Button();
			this.Cancel = new System.Windows.Forms.Button();
			this.Browser = new System.Windows.Forms.Button();
			this.LibPath = new System.Windows.Forms.TextBox();
			this.SuspendLayout();
			// 
			// treeView
			// 
			this.treeView.ImageList = this.imageList;
			this.treeView.Location = new System.Drawing.Point(8, 8);
			this.treeView.Name = "treeView";
			this.treeView.Size = new System.Drawing.Size(264, 272);
			this.treeView.TabIndex = 0;
			this.treeView.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.treeView_AfterSelect);
			// 
			// imageList
			// 
			this.imageList.ImageSize = new System.Drawing.Size(16, 16);
			this.imageList.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList.ImageStream")));
			this.imageList.TransparentColor = System.Drawing.Color.Transparent;
			// 
			// PlaceBolts
			// 
			this.PlaceBolts.Enabled = false;
			this.PlaceBolts.Location = new System.Drawing.Point(280, 16);
			this.PlaceBolts.Name = "PlaceBolts";
			this.PlaceBolts.TabIndex = 1;
			this.PlaceBolts.Text = "Place Bolts";
			this.PlaceBolts.Click += new System.EventHandler(this.PlaceBolts_Click);
			// 
			// Cancel
			// 
			this.Cancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.Cancel.Location = new System.Drawing.Point(280, 56);
			this.Cancel.Name = "Cancel";
			this.Cancel.TabIndex = 2;
			this.Cancel.Text = "Cancel";
			this.Cancel.Click += new System.EventHandler(this.Cancel_Click);
			// 
			// Browser
			// 
			this.Browser.Location = new System.Drawing.Point(280, 288);
			this.Browser.Name = "Browser";
			this.Browser.TabIndex = 3;
			this.Browser.Text = "Browse...";
			this.Browser.Click += new System.EventHandler(this.Browser_Click);
			// 
			// LibPath
			// 
			this.LibPath.Location = new System.Drawing.Point(8, 288);
			this.LibPath.Name = "LibPath";
			this.LibPath.Size = new System.Drawing.Size(264, 20);
			this.LibPath.TabIndex = 4;
			this.LibPath.Text = "";
			// 
			// Form1
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(360, 317);
			this.Controls.Add(this.LibPath);
			this.Controls.Add(this.Browser);
			this.Controls.Add(this.Cancel);
			this.Controls.Add(this.PlaceBolts);
			this.Controls.Add(this.treeView);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
			this.MaximizeBox = false;
			this.Name = "Form1";
			this.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "AutoBolts Dialog";
			this.ResumeLayout(false);

		}
		#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			System.Windows.Forms.Application.Run(new Form1());			
		}
	
		protected override void OnLoad(EventArgs e)
		{	
			m_BoltPlacer = new BoltPlacer();	
			if( !m_BoltPlacer.Init( treeView ) )
			{
				this.Close();	
			}

			string libPath = System.IO.Directory.GetCurrentDirectory() + "\\..\\..\\" + "Bolt Library";
			this.LibPath.Text = libPath;
           	m_BoltPlacer.LibaryPath = libPath;

			base.OnLoad (e);
		}

		private void Cancel_Click(object sender, System.EventArgs e)
		{
			this.Close();
		}

		private void treeView_AfterSelect(object sender, System.Windows.Forms.TreeViewEventArgs e)
		{
			TreeNode selNode = e.Node;
			if( selNode.Tag==null )
				return;
			
			int index = (int)selNode.Tag;

			if( m_BoltPlacer.CanPlaceBolts(index) )			
				PlaceBolts.Enabled = true;			
			else
				PlaceBolts.Enabled = false;
		}

		private void PlaceBolts_Click(object sender, System.EventArgs e)
		{
			TreeNode selNode = treeView.SelectedNode;
			if( selNode.Tag!=null )
			{
				int index = (int)selNode.Tag;
				m_BoltPlacer.ExecutePlaceBolts( index );				
			}
		}

		private void Browser_Click(object sender, System.EventArgs e)
		{
			FolderBrowserDialog LibrarySelectionDialog = new FolderBrowserDialog();
			LibrarySelectionDialog.Description = "Bolt Library Path:";			
			if( LibrarySelectionDialog.ShowDialog()==DialogResult.OK )
			{
				this.LibPath.Text = LibrarySelectionDialog.SelectedPath;
			}			
		}
	}
}
