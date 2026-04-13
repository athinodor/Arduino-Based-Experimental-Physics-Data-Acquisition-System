<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()>
Partial Class frmSaveArduinoData
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()>
    Protected Overrides Sub Dispose(disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()>
    Private Sub InitializeComponent()
        btnStart = New Button()
        btnStop = New Button()
        txtData = New TextBox()
        btnCloseApp = New Button()
        Label1 = New Label()
        cmbPort = New ComboBox()
        Label2 = New Label()
        Label3 = New Label()
        txtFileName = New TextBox()
        Label4 = New Label()
        fbdSaveFolder = New FolderBrowserDialog()
        btnSelectFolder = New Button()
        txtSaveFolder = New TextBox()
        btnCreateFile = New Button()
        btnClearFileData = New Button()
        SuspendLayout()
        ' 
        ' btnStart
        ' 
        btnStart.Location = New Point(12, 143)
        btnStart.Margin = New Padding(3, 4, 3, 4)
        btnStart.Name = "btnStart"
        btnStart.Size = New Size(158, 40)
        btnStart.TabIndex = 0
        btnStart.Text = "Έναρξη Καταγραφής"
        btnStart.UseVisualStyleBackColor = True
        ' 
        ' btnStop
        ' 
        btnStop.Location = New Point(176, 143)
        btnStop.Margin = New Padding(3, 4, 3, 4)
        btnStop.Name = "btnStop"
        btnStop.Size = New Size(173, 40)
        btnStop.TabIndex = 1
        btnStop.Text = "Διακοπή Καταγραφής"
        btnStop.UseVisualStyleBackColor = True
        ' 
        ' txtData
        ' 
        txtData.Location = New Point(3, 222)
        txtData.Margin = New Padding(3, 4, 3, 4)
        txtData.Multiline = True
        txtData.Name = "txtData"
        txtData.ScrollBars = ScrollBars.Vertical
        txtData.Size = New Size(340, 479)
        txtData.TabIndex = 2
        ' 
        ' btnCloseApp
        ' 
        btnCloseApp.Location = New Point(400, 279)
        btnCloseApp.Margin = New Padding(3, 4, 3, 4)
        btnCloseApp.Name = "btnCloseApp"
        btnCloseApp.Size = New Size(158, 40)
        btnCloseApp.TabIndex = 3
        btnCloseApp.Text = "Τερματισμός"
        btnCloseApp.UseVisualStyleBackColor = True
        ' 
        ' Label1
        ' 
        Label1.AutoSize = True
        Label1.Location = New Point(3, 198)
        Label1.Name = "Label1"
        Label1.Size = New Size(134, 20)
        Label1.TabIndex = 4
        Label1.Text = "Δεδομένα Arduino"
        ' 
        ' cmbPort
        ' 
        cmbPort.DisplayMember = "COM1"
        cmbPort.DropDownStyle = ComboBoxStyle.DropDownList
        cmbPort.FormattingEnabled = True
        cmbPort.Items.AddRange(New Object() {"COM1", "COM2", "COM3", "COM4", "COM5", "COM6"})
        cmbPort.Location = New Point(176, 76)
        cmbPort.Margin = New Padding(3, 4, 3, 4)
        cmbPort.Name = "cmbPort"
        cmbPort.Size = New Size(138, 28)
        cmbPort.TabIndex = 5
        cmbPort.ValueMember = "COM1"
        ' 
        ' Label2
        ' 
        Label2.AutoSize = True
        Label2.Location = New Point(3, 79)
        Label2.Name = "Label2"
        Label2.Size = New Size(111, 20)
        Label2.TabIndex = 6
        Label2.Text = "Σειριακή Θύρα:"
        ' 
        ' Label3
        ' 
        Label3.AutoSize = True
        Label3.Location = New Point(3, 41)
        Label3.Name = "Label3"
        Label3.Size = New Size(156, 20)
        Label3.TabIndex = 7
        Label3.Text = "Αρχείο αποθήκευσης:"
        ' 
        ' txtFileName
        ' 
        txtFileName.Location = New Point(176, 41)
        txtFileName.Margin = New Padding(3, 4, 3, 4)
        txtFileName.Name = "txtFileName"
        txtFileName.Size = New Size(139, 27)
        txtFileName.TabIndex = 8
        txtFileName.Text = "arduino_data.csv"
        ' 
        ' Label4
        ' 
        Label4.AutoSize = True
        Label4.Location = New Point(3, 9)
        Label4.Name = "Label4"
        Label4.Size = New Size(167, 20)
        Label4.TabIndex = 9
        Label4.Text = "Φάκελος αποθήκευσης:"
        ' 
        ' btnSelectFolder
        ' 
        btnSelectFolder.Location = New Point(556, 4)
        btnSelectFolder.Margin = New Padding(3, 4, 3, 4)
        btnSelectFolder.Name = "btnSelectFolder"
        btnSelectFolder.Size = New Size(40, 31)
        btnSelectFolder.TabIndex = 10
        btnSelectFolder.Text = "..."
        btnSelectFolder.UseVisualStyleBackColor = True
        ' 
        ' txtSaveFolder
        ' 
        txtSaveFolder.Location = New Point(176, 7)
        txtSaveFolder.Name = "txtSaveFolder"
        txtSaveFolder.Size = New Size(374, 27)
        txtSaveFolder.TabIndex = 11
        ' 
        ' btnCreateFile
        ' 
        btnCreateFile.Location = New Point(339, 79)
        btnCreateFile.Name = "btnCreateFile"
        btnCreateFile.Size = New Size(190, 29)
        btnCreateFile.TabIndex = 12
        btnCreateFile.Text = "Δημιουργία Αρχείου"
        btnCreateFile.UseVisualStyleBackColor = True
        ' 
        ' btnClearFileData
        ' 
        btnClearFileData.Location = New Point(355, 143)
        btnClearFileData.Name = "btnClearFileData"
        btnClearFileData.Size = New Size(174, 40)
        btnClearFileData.TabIndex = 13
        btnClearFileData.Text = "Καθάρισμα Αρχείου"
        btnClearFileData.UseVisualStyleBackColor = True
        ' 
        ' frmSaveArduinoData
        ' 
        AutoScaleDimensions = New SizeF(8F, 20F)
        AutoScaleMode = AutoScaleMode.Font
        ClientSize = New Size(598, 702)
        Controls.Add(btnClearFileData)
        Controls.Add(btnCreateFile)
        Controls.Add(txtSaveFolder)
        Controls.Add(btnSelectFolder)
        Controls.Add(Label4)
        Controls.Add(txtFileName)
        Controls.Add(Label3)
        Controls.Add(Label2)
        Controls.Add(cmbPort)
        Controls.Add(Label1)
        Controls.Add(btnCloseApp)
        Controls.Add(txtData)
        Controls.Add(btnStop)
        Controls.Add(btnStart)
        Margin = New Padding(3, 4, 3, 4)
        Name = "frmSaveArduinoData"
        Text = "Save Arduino Data"
        ResumeLayout(False)
        PerformLayout()
    End Sub

    Friend WithEvents btnStart As Button
    Friend WithEvents btnStop As Button
    Friend WithEvents txtData As TextBox
    Friend WithEvents btnCloseApp As Button
    Friend WithEvents Label1 As Label
    Friend WithEvents cmbPort As ComboBox
    Friend WithEvents Label2 As Label
    Friend WithEvents Label3 As Label
    Friend WithEvents txtFileName As TextBox
    Friend WithEvents Label4 As Label
    Friend WithEvents fbdSaveFolder As FolderBrowserDialog
    Friend WithEvents btnSelectFolder As Button
    Friend WithEvents txtSaveFolder As TextBox
    Friend WithEvents btnCreateFile As Button
    Friend WithEvents btnClearFileData As Button

End Class
