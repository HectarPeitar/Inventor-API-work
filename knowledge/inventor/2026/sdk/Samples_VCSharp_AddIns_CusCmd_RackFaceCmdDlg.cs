using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using Inventor;

namespace CustomCommand
{
	internal class RackFaceCmdDlg : System.Windows.Forms.Form
	{
		public System.Windows.Forms.CheckBox checkBoxFace;
		public System.Windows.Forms.CheckBox checkBoxDirection;
		private System.Windows.Forms.Button buttonHelp;
		public System.Windows.Forms.Button buttonOK;
		private System.Windows.Forms.Button buttonCancel;
		private System.Windows.Forms.GroupBox groupBoxRackParams;
		private System.Windows.Forms.GroupBox groupBoxExtents;
		private System.Windows.Forms.RadioButton radioButtonNegativeExtent;
		private System.Windows.Forms.RadioButton radioButtonPositiveExtent;
		private System.Windows.Forms.RadioButton radioButtonSymmetricExtent;
		private System.Windows.Forms.TextBox textBoxNumOfTeeth;
		private System.Windows.Forms.TextBox textBoxHeight;
		private System.Windows.Forms.TextBox textBoxWidth;
		private System.Windows.Forms.TextBox textBoxExtentsEdit;
		private System.Windows.Forms.Label labelWidth;
		private System.Windows.Forms.Label labelHeight;
		private System.Windows.Forms.Label labelTeeth;
		private System.Windows.Forms.Label labelFace;
		private System.Windows.Forms.Label labelDirection;	
		private System.Windows.Forms.ToolTip toolTip;
		
		public string m_rackHeight;
		public string m_rackWidth;
		public string m_noTeeth;
		public string m_rackExtents;
		public int m_rackExtentsDirection;
		
		private Inventor.Application m_application;
		private RackFaceCmd m_rackFaceCmd;
		private System.ComponentModel.IContainer components;

		public RackFaceCmdDlg(Inventor.Application application, RackFaceCmd rackFaceCmd)
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();
			
			m_application = application;
			m_rackFaceCmd = rackFaceCmd;
		
			m_rackHeight = "0.1";
			m_rackWidth = "0.50";
			m_noTeeth = "5";
			m_rackExtents = "1.0";
			m_rackExtentsDirection = 0;

			buttonOK.Enabled = false;
			checkBoxFace.Checked = true;

			radioButtonNegativeExtent.Checked = true;
		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if(components != null)
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
			System.Resources.ResourceManager resources = new System.Resources.ResourceManager(typeof(RackFaceCmdDlg));
			this.checkBoxFace = new System.Windows.Forms.CheckBox();
			this.checkBoxDirection = new System.Windows.Forms.CheckBox();
			this.buttonHelp = new System.Windows.Forms.Button();
			this.buttonOK = new System.Windows.Forms.Button();
			this.buttonCancel = new System.Windows.Forms.Button();
			this.groupBoxRackParams = new System.Windows.Forms.GroupBox();
			this.labelWidth = new System.Windows.Forms.Label();
			this.labelHeight = new System.Windows.Forms.Label();
			this.labelTeeth = new System.Windows.Forms.Label();
			this.groupBoxExtents = new System.Windows.Forms.GroupBox();
			this.radioButtonSymmetricExtent = new System.Windows.Forms.RadioButton();
			this.radioButtonPositiveExtent = new System.Windows.Forms.RadioButton();
			this.radioButtonNegativeExtent = new System.Windows.Forms.RadioButton();
			this.textBoxExtentsEdit = new System.Windows.Forms.TextBox();
			this.textBoxWidth = new System.Windows.Forms.TextBox();
			this.textBoxHeight = new System.Windows.Forms.TextBox();
			this.textBoxNumOfTeeth = new System.Windows.Forms.TextBox();
			this.labelFace = new System.Windows.Forms.Label();
			this.labelDirection = new System.Windows.Forms.Label();
			this.toolTip = new System.Windows.Forms.ToolTip(this.components);
			this.groupBoxRackParams.SuspendLayout();
			this.groupBoxExtents.SuspendLayout();
			this.SuspendLayout();
			// 
			// checkBoxFace
			// 
			this.checkBoxFace.Appearance = System.Windows.Forms.Appearance.Button;
			this.checkBoxFace.Image = ((System.Drawing.Image)(resources.GetObject("checkBoxFace.Image")));
			this.checkBoxFace.Location = new System.Drawing.Point(15, 16);
			this.checkBoxFace.Name = "checkBoxFace";
			this.checkBoxFace.Size = new System.Drawing.Size(29, 25);
			this.checkBoxFace.TabIndex = 0;
			this.checkBoxFace.Click += new System.EventHandler(this.OnSelectRackFaceButton);
			// 
			// checkBoxDirection
			// 
			this.checkBoxDirection.Appearance = System.Windows.Forms.Appearance.Button;
			this.checkBoxDirection.Image = ((System.Drawing.Image)(resources.GetObject("checkBoxDirection.Image")));
			this.checkBoxDirection.Location = new System.Drawing.Point(15, 56);
			this.checkBoxDirection.Name = "checkBoxDirection";
			this.checkBoxDirection.Size = new System.Drawing.Size(29, 25);
			this.checkBoxDirection.TabIndex = 1;
			this.checkBoxDirection.Click += new System.EventHandler(this.OnSelectRackDirectionButton);
			// 
			// buttonHelp
			// 
			this.buttonHelp.Image = ((System.Drawing.Image)(resources.GetObject("buttonHelp.Image")));
			this.buttonHelp.Location = new System.Drawing.Point(15, 183);
			this.buttonHelp.Name = "buttonHelp";
			this.buttonHelp.Size = new System.Drawing.Size(29, 25);
			this.buttonHelp.TabIndex = 2;
			this.buttonHelp.Click += new System.EventHandler(this.OnHelpButton);
			// 
			// buttonOK
			// 
			this.buttonOK.Location = new System.Drawing.Point(159, 185);
			this.buttonOK.Name = "buttonOK";
			this.buttonOK.TabIndex = 3;
			this.buttonOK.Text = "OK";
			this.buttonOK.Click += new System.EventHandler(this.OnOK);
			// 
			// buttonCancel
			// 
			this.buttonCancel.Location = new System.Drawing.Point(255, 185);
			this.buttonCancel.Name = "buttonCancel";
			this.buttonCancel.TabIndex = 4;
			this.buttonCancel.Text = "Cancel";
			this.buttonCancel.Click += new System.EventHandler(this.OnCancel);
			// 
			// groupBoxRackParams
			// 
			this.groupBoxRackParams.Controls.Add(this.labelWidth);
			this.groupBoxRackParams.Controls.Add(this.labelHeight);
			this.groupBoxRackParams.Controls.Add(this.labelTeeth);
			this.groupBoxRackParams.Controls.Add(this.groupBoxExtents);
			this.groupBoxRackParams.Controls.Add(this.textBoxWidth);
			this.groupBoxRackParams.Controls.Add(this.textBoxHeight);
			this.groupBoxRackParams.Controls.Add(this.textBoxNumOfTeeth);
			this.groupBoxRackParams.Location = new System.Drawing.Point(106, 14);
			this.groupBoxRackParams.Name = "groupBoxRackParams";
			this.groupBoxRackParams.Size = new System.Drawing.Size(224, 157);
			this.groupBoxRackParams.TabIndex = 0;
			this.groupBoxRackParams.Text = "Rack Parameters";
			// 
			// labelWidth
			// 
			this.labelWidth.Location = new System.Drawing.Point(32, 84);
			this.labelWidth.Name = "labelWidth";
			this.labelWidth.Size = new System.Drawing.Size(64, 20);
			this.labelWidth.TabIndex = 6;
			this.labelWidth.Text = "Width";
			// 
			// labelHeight
			// 
			this.labelHeight.Location = new System.Drawing.Point(32, 53);
			this.labelHeight.Name = "labelHeight";
			this.labelHeight.Size = new System.Drawing.Size(64, 20);
			this.labelHeight.TabIndex = 5;
			this.labelHeight.Text = "Height";
			// 
			// labelTeeth
			// 
			this.labelTeeth.Location = new System.Drawing.Point(32, 22);
			this.labelTeeth.Name = "labelTeeth";
			this.labelTeeth.Size = new System.Drawing.Size(64, 20);
			this.labelTeeth.TabIndex = 4;
			this.labelTeeth.Text = "No. of teeth";
			// 
			// groupBoxExtents
			// 
			this.groupBoxExtents.Controls.Add(this.radioButtonSymmetricExtent);
			this.groupBoxExtents.Controls.Add(this.radioButtonPositiveExtent);
			this.groupBoxExtents.Controls.Add(this.radioButtonNegativeExtent);
			this.groupBoxExtents.Controls.Add(this.textBoxExtentsEdit);
			this.groupBoxExtents.Location = new System.Drawing.Point(8, 108);
			this.groupBoxExtents.Name = "groupBoxExtents";
			this.groupBoxExtents.Size = new System.Drawing.Size(210, 42);
			this.groupBoxExtents.TabIndex = 3;
			this.groupBoxExtents.TabStop = false;
			this.groupBoxExtents.Text = "Extents";
			// 
			// radioButtonSymmetricExtent
			// 
			this.radioButtonSymmetricExtent.Appearance = System.Windows.Forms.Appearance.Button;
			this.radioButtonSymmetricExtent.Image = ((System.Drawing.Image)(resources.GetObject("radioButtonSymmetricExtent.Image")));
			this.radioButtonSymmetricExtent.Location = new System.Drawing.Point(174, 12);
			this.radioButtonSymmetricExtent.Name = "radioButtonSymmetricExtent";
			this.radioButtonSymmetricExtent.Size = new System.Drawing.Size(29, 24);
			this.radioButtonSymmetricExtent.TabIndex = 3;
			this.toolTip.SetToolTip(this.radioButtonSymmetricExtent, "Symmetric");
			this.radioButtonSymmetricExtent.Click += new System.EventHandler(this.OnRackSymmetricExtentsButton);
			// 
			// radioButtonPositiveExtent
			// 
			this.radioButtonPositiveExtent.Appearance = System.Windows.Forms.Appearance.Button;
			this.radioButtonPositiveExtent.Image = ((System.Drawing.Image)(resources.GetObject("radioButtonPositiveExtent.Image")));
			this.radioButtonPositiveExtent.Location = new System.Drawing.Point(144, 12);
			this.radioButtonPositiveExtent.Name = "radioButtonPositiveExtent";
			this.radioButtonPositiveExtent.Size = new System.Drawing.Size(29, 24);
			this.radioButtonPositiveExtent.TabIndex = 2;
			this.toolTip.SetToolTip(this.radioButtonPositiveExtent, "Positive");
			this.radioButtonPositiveExtent.Click += new System.EventHandler(this.OnRackPositiveExtentsButton);
			// 
			// radioButtonNegativeExtent
			// 
			this.radioButtonNegativeExtent.Appearance = System.Windows.Forms.Appearance.Button;
			this.radioButtonNegativeExtent.Image = ((System.Drawing.Image)(resources.GetObject("radioButtonNegativeExtent.Image")));
			this.radioButtonNegativeExtent.Location = new System.Drawing.Point(114, 12);
			this.radioButtonNegativeExtent.Name = "radioButtonNegativeExtent";
			this.radioButtonNegativeExtent.Size = new System.Drawing.Size(29, 24);
			this.radioButtonNegativeExtent.TabIndex = 1;
			this.toolTip.SetToolTip(this.radioButtonNegativeExtent, "Negative");
			this.radioButtonNegativeExtent.Click += new System.EventHandler(this.OnRackNegativeExtentsButton);
			// 
			// textBoxExtentsEdit
			// 
			this.textBoxExtentsEdit.AcceptsTab = true;
			this.textBoxExtentsEdit.Location = new System.Drawing.Point(7, 14);
			this.textBoxExtentsEdit.Name = "textBoxExtentsEdit";
			this.textBoxExtentsEdit.TabIndex = 3;
			this.textBoxExtentsEdit.Text = "1.0";
			this.textBoxExtentsEdit.TextChanged += new System.EventHandler(this.OnChangeRackExtentsEdit);
			// 
			// textBoxWidth
			// 
			this.textBoxWidth.AcceptsTab = true;
			this.textBoxWidth.Location = new System.Drawing.Point(103, 83);
			this.textBoxWidth.Name = "textBoxWidth";
			this.textBoxWidth.Size = new System.Drawing.Size(114, 20);
			this.textBoxWidth.TabIndex = 2;
			this.textBoxWidth.Text = "0.50";
			this.textBoxWidth.TextChanged += new System.EventHandler(this.OnChangeRackWidthEdit);
			// 
			// textBoxHeight
			// 
			this.textBoxHeight.AcceptsTab = true;
			this.textBoxHeight.Location = new System.Drawing.Point(103, 52);
			this.textBoxHeight.Name = "textBoxHeight";
			this.textBoxHeight.Size = new System.Drawing.Size(114, 20);
			this.textBoxHeight.TabIndex = 1;
			this.textBoxHeight.Text = "0.1";
			this.textBoxHeight.TextChanged += new System.EventHandler(this.OnChangeRackHeightEdit);
			// 
			// textBoxNumOfTeeth
			// 
			this.textBoxNumOfTeeth.AcceptsTab = true;
			this.textBoxNumOfTeeth.Location = new System.Drawing.Point(103, 21);
			this.textBoxNumOfTeeth.Name = "textBoxNumOfTeeth";
			this.textBoxNumOfTeeth.Size = new System.Drawing.Size(114, 20);
			this.textBoxNumOfTeeth.TabIndex = 0;
			this.textBoxNumOfTeeth.Text = "5";
			this.textBoxNumOfTeeth.TextChanged += new System.EventHandler(this.OnChangeTeethNumberEdit);
			// 
			// labelFace
			// 
			this.labelFace.Location = new System.Drawing.Point(50, 15);
			this.labelFace.Name = "labelFace";
			this.labelFace.Size = new System.Drawing.Size(32, 23);
			this.labelFace.TabIndex = 6;
			this.labelFace.Text = "Face";
			// 
			// labelDirection
			// 
			this.labelDirection.Location = new System.Drawing.Point(50, 55);
			this.labelDirection.Name = "labelDirection";
			this.labelDirection.Size = new System.Drawing.Size(51, 23);
			this.labelDirection.TabIndex = 7;
			this.labelDirection.Text = "Direction";
			// 
			// RackFaceCmdDlg
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(344, 223);
			this.Controls.Add(this.labelDirection);
			this.Controls.Add(this.labelFace);
			this.Controls.Add(this.groupBoxRackParams);
			this.Controls.Add(this.buttonCancel);
			this.Controls.Add(this.buttonOK);
			this.Controls.Add(this.buttonHelp);
			this.Controls.Add(this.checkBoxDirection);
			this.Controls.Add(this.checkBoxFace);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.KeyPreview = true;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "RackFaceCmdDlg";
			this.Text = "Rack Face";
			this.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.RackFaceCmdDlg_KeyPress);
			this.Closed += new System.EventHandler(this.OnClose);
			this.groupBoxRackParams.ResumeLayout(false);
			this.groupBoxExtents.ResumeLayout(false);
			this.ResumeLayout(false);

		}
		#endregion

		private void RackFaceCmdDlg_KeyPress(object sender, KeyPressEventArgs e)
		{
			//"Esc" key cancels command
			if (e.KeyChar == 27)
			{
				m_rackFaceCmd.StopCommand();
			}
		}

		private void OnSelectRackDirectionButton(object sender, System.EventArgs e)
		{
			//disable rack face selection button
			checkBoxFace.Checked = false;

			//if selected then start direction selection
			if (checkBoxDirection.Checked)
			{
				m_rackFaceCmd.EnableInteraction();
			}
			else
			{
				m_rackFaceCmd.DisableInteraction();
			}
		}

		private void OnSelectRackFaceButton(object sender, System.EventArgs e)
		{
			//disable rack direction selection button
			checkBoxDirection.Checked = false;

			//if selected then start face selection
			if (checkBoxFace.Checked)
			{
				m_rackFaceCmd.EnableInteraction();
			}
			else
			{
				m_rackFaceCmd.DisableInteraction();
			}	
		}

		private void OnChangeTeethNumberEdit(object sender, System.EventArgs e)
		{
			//reject invalid input
			if (!ValidateIntInput(textBoxNumOfTeeth.Text.Trim()))
			{
				textBoxNumOfTeeth.ForeColor = System.Drawing.Color.Red;
				buttonOK.Enabled = false;
			}
			else //input for this parameter is validated
			{
				textBoxNumOfTeeth.ForeColor = System.Drawing.Color.Black;
				m_noTeeth = textBoxNumOfTeeth.Text;					
				m_rackFaceCmd.UpdateCommandStatus();
			}
		}

		private void OnChangeRackHeightEdit(object sender, System.EventArgs e)
		{
            double dHeight = m_rackFaceCmd.GetValueFromExpression(textBoxHeight.Text.Trim());
			//reject invalid input
            if (!ValidateFloatInput(dHeight.ToString()))
			{
				textBoxHeight.ForeColor = System.Drawing.Color.Red;
				buttonOK.Enabled = false;
			}
			else //input for this parameter is validated
			{
				textBoxHeight.ForeColor = System.Drawing.Color.Black;
				m_rackHeight = textBoxHeight.Text;			
				m_rackFaceCmd.UpdateCommandStatus();
			}			
		}

		private void OnChangeRackWidthEdit(object sender, System.EventArgs e)
		{
            double dWidth = m_rackFaceCmd.GetValueFromExpression(textBoxWidth.Text.Trim());
			//reject invalid input
            if (!ValidateFloatInput(dWidth.ToString()))
			{
				textBoxWidth.ForeColor = System.Drawing.Color.Red;
				buttonOK.Enabled = false;
			}
			else //input for this parameter is validated
			{
				textBoxWidth.ForeColor = System.Drawing.Color.Black;
				m_rackWidth = textBoxWidth.Text;							
				m_rackFaceCmd.UpdateCommandStatus();
			}	
		}

		private void OnChangeRackExtentsEdit(object sender, System.EventArgs e)
		{
            double dExtent = m_rackFaceCmd.GetValueFromExpression(textBoxExtentsEdit.Text.Trim());
			//reject invalid input
            if (!ValidateFloatInput(dExtent.ToString()))
			{
				textBoxExtentsEdit.ForeColor = System.Drawing.Color.Red;
				buttonOK.Enabled = false;
			}
			else
			{
				//input for this parameter is validated
				textBoxExtentsEdit.ForeColor = System.Drawing.Color.Black;
				m_rackExtents = textBoxExtentsEdit.Text;							
				m_rackFaceCmd.UpdateCommandStatus();
			}		
		}

		private void OnRackNegativeExtentsButton(object sender, System.EventArgs e)
		{
			m_rackExtentsDirection = 0;
			m_rackFaceCmd.UpdateCommandStatus();
		}

		private void OnRackPositiveExtentsButton(object sender, System.EventArgs e)
		{
			m_rackExtentsDirection = 1;
			m_rackFaceCmd.UpdateCommandStatus();
		}

		private void OnRackSymmetricExtentsButton(object sender, System.EventArgs e)
		{
			m_rackExtentsDirection = 2;
			m_rackFaceCmd.UpdateCommandStatus();
		}

		private void OnOK(object sender, System.EventArgs e)
		{
			m_rackFaceCmd.ExecuteCommand();
		}

		private void OnCancel(object sender, System.EventArgs e)
		{
			m_rackFaceCmd.StopCommand();
		}

		private void OnClose(object sender, System.EventArgs e)
		{
			m_rackFaceCmd.StopCommand();
		}

		private void OnHelpButton(object sender, System.EventArgs e)
		{
			//get the help manager object and display the start page of the "Inventor API" help
			m_application.HelpManager.DisplayHelpTopic("ADMAPI_12_0.chm", "");
		}

		private bool ValidateIntInput(string input)
		{
			try
			{
				int num = int.Parse(input);
				if (num <= 0)
				{
					return false;
				}
			}
			catch
			{
				return false;
			}

			return true;
		}

		private bool ValidateFloatInput(string input)
		{
			try
			{
				float num = float.Parse(input);
				if (num <= 0)
				{
					return false;
				}
			}
			catch
			{
				return false;
			}

			return true;
		}

		public bool AllParametersAreValid()
		{
			return (
				    (textBoxNumOfTeeth.ForeColor != System.Drawing.Color.Red)
				    &&
				    (textBoxHeight.ForeColor != System.Drawing.Color.Red)
                    &&
                    (textBoxWidth.ForeColor != System.Drawing.Color.Red)
				    &&
				    (textBoxExtentsEdit.ForeColor != System.Drawing.Color.Red)
				   );
		}
	}
}