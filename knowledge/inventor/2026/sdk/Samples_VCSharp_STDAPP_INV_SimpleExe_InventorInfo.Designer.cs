namespace SimpleExe
{
    partial class InventorInfo
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.btnClose = new System.Windows.Forms.Button();
            this.lstViewInvInfo = new System.Windows.Forms.ListView();
            this.propertyColumnHeader = new System.Windows.Forms.ColumnHeader();
            this.valueColumnHeader = new System.Windows.Forms.ColumnHeader();
            this.SuspendLayout();
            // 
            // btnClose
            // 
            this.btnClose.Location = new System.Drawing.Point(322, 275);
            this.btnClose.Name = "btnClose";
            this.btnClose.Size = new System.Drawing.Size(110, 42);
            this.btnClose.TabIndex = 0;
            this.btnClose.Text = "Close";
            this.btnClose.UseVisualStyleBackColor = true;
            this.btnClose.Click += new System.EventHandler(this.btnClose_Click);
            // 
            // lstViewInvInfo
            // 
            this.lstViewInvInfo.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.propertyColumnHeader,
            this.valueColumnHeader});
            this.lstViewInvInfo.Location = new System.Drawing.Point(23, 25);
            this.lstViewInvInfo.Name = "lstViewInvInfo";
            this.lstViewInvInfo.Size = new System.Drawing.Size(409, 233);
            this.lstViewInvInfo.TabIndex = 1;
            this.lstViewInvInfo.UseCompatibleStateImageBehavior = false;
            this.lstViewInvInfo.View = System.Windows.Forms.View.Details;
            // 
            // propertyColumnHeader
            // 
            this.propertyColumnHeader.Text = "Property";
            this.propertyColumnHeader.Width = 108;
            // 
            // valueColumnHeader
            // 
            this.valueColumnHeader.Text = "Value";
            this.valueColumnHeader.Width = 300;
            // 
            // InventorInfo
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(479, 344);
            this.Controls.Add(this.lstViewInvInfo);
            this.Controls.Add(this.btnClose);
            this.Name = "InventorInfo";
            this.Text = "Inventor Information";
            this.Load += new System.EventHandler(this.InventorInfo_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btnClose;
        private System.Windows.Forms.ListView lstViewInvInfo;
        private System.Windows.Forms.ColumnHeader propertyColumnHeader;
        private System.Windows.Forms.ColumnHeader valueColumnHeader;
    }
}

