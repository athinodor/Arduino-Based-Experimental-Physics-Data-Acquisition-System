Imports System.IO
Imports System.IO.Ports
Imports System.Windows.Forms.VisualStyles.VisualStyleElement

Public Class frmSaveArduinoData
    Dim WithEvents SerialPort1 As New SerialPort
    Dim filePath As String '= "C:\Users\3lykpyrgportable1\OneDrive\Έγγραφα\arduino_data.csv" ' "C:\arduino_data.csv"
    Dim loggingEnabled As Boolean = False
    Private Sub frmSaveArduinoData_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        ' Ρύθμιση σειριακής θύρας (άλλαξε COM ανάλογα με το Arduino σου)
        cmbPort.SelectedIndex = 3
        SerialPort1.PortName = cmbPort.Text
        SerialPort1.BaudRate = 9600





    End Sub

    Private Sub btnStart_Click(sender As Object, e As EventArgs) Handles btnStart.Click
        Try
            If Not SerialPort1.IsOpen Then
                SerialPort1.Open()
            End If

            loggingEnabled = True
            txtData.AppendText("▶ Καταγραφή ξεκίνησε..." & Environment.NewLine)
        Catch ex As Exception
            MessageBox.Show("Σφάλμα: " & ex.Message)
        End Try
    End Sub

    Private Sub btnStop_Click(sender As Object, e As EventArgs) Handles btnStop.Click
        loggingEnabled = False
        txtData.AppendText("■ Καταγραφή σταμάτησε." & Environment.NewLine)
    End Sub

    Private Sub SerialPort1_DataReceived(sender As Object, e As SerialDataReceivedEventArgs) Handles SerialPort1.DataReceived
        Try
            Dim line As String = SerialPort1.ReadLine().Trim()

            If loggingEnabled Then
                Dim output As String = $"{line}" '$"{DateTime.Now},{line}"
                File.AppendAllText(filePath, output & Environment.NewLine)

                Me.Invoke(Sub()
                              txtData.AppendText(output & Environment.NewLine)
                          End Sub)
            End If
        Catch ex As Exception
            ' αγνόησε σφάλματα ανάγνωσης
        End Try
    End Sub

    Private Sub frmSaveArduinoData_FormClosing(sender As Object, e As FormClosingEventArgs) Handles Me.FormClosing
        If SerialPort1.IsOpen Then SerialPort1.Close()
    End Sub

    Private Sub btnSelectFolder_Click(sender As Object, e As EventArgs) Handles btnSelectFolder.Click

        Using dlg As New FolderBrowserDialog()
            dlg.Description = "Επιλέξτε φάκελο αποθήκευσης"
            dlg.ShowNewFolderButton = True

            ' Προεπιλογή στον φάκελο του current filePath αν υπάρχει
            Try
                Dim currentDir As String = If(String.IsNullOrWhiteSpace(txtSaveFolder.Text),
                                              Path.GetDirectoryName(filePath),
                                              txtSaveFolder.Text)
                If Not String.IsNullOrWhiteSpace(currentDir) AndAlso Directory.Exists(currentDir) Then
                    dlg.SelectedPath = currentDir
                End If
            Catch
                ' αγνόησε τυχόν σφάλματα στην ανάγνωση του path
            End Try

            If dlg.ShowDialog() = DialogResult.OK Then
                txtSaveFolder.Text = dlg.SelectedPath
            End If
        End Using

    End Sub


    Private Sub cmbPort_SelectedIndexChanged(sender As Object, e As EventArgs) Handles cmbPort.SelectedIndexChanged
        SerialPort1.PortName = cmbPort.Text
    End Sub

    Private Sub btnCreateFile_Click(sender As Object, e As EventArgs) Handles btnCreateFile.Click
        filePath = txtSaveFolder.Text & "\" & txtFileName.Text
        If filePath = "\" Then
            MsgBox("Επιλέξτε φάκελο και όνομα αρχείου για αποθήκευση δεδομένων.", MsgBoxStyle.Exclamation, "Προσοχή")
        Else

            ' Δημιουργία αρχείου αν δεν υπάρχει
            If Not File.Exists(filePath) Then
                'File.WriteAllText(filePath, "Χρόνος,Απόσταση (cm)" & Environment.NewLine)
                File.WriteAllText(filePath, "t (s),x (cm),V (cm/s),a (cm/s^2)" & Environment.NewLine)
            End If

        End If

    End Sub

    Private Sub btnCloseApp_Click(sender As Object, e As EventArgs) Handles btnCloseApp.Click
        ' Αν υπάρχει ενεργή καταγραφή, ρώτησε τον χρήστη
        If loggingEnabled Then
            Dim res As DialogResult = MessageBox.Show("Υπάρχει ενεργή καταγραφή. Να σταματήσει η καταγραφή και να κλείσει η εφαρμογή;", "Επιβεβαίωση", MessageBoxButtons.YesNo, MessageBoxIcon.Question)
            If res = DialogResult.No Then
                Return
            End If
        End If

        ' Σιγουρέψου ότι η καταγραφή σταμάτησε και η θύρα έκλεισε
        loggingEnabled = False
        Try
            If SerialPort1 IsNot Nothing AndAlso SerialPort1.IsOpen Then
                SerialPort1.Close()
            End If
        Catch ex As Exception
            ' Μπορείς να το καταγράψεις αν θες, αλλά δεν είναι κρίσιμο
        End Try

        ' Κλείσιμο της φόρμας (θα τρέξει το FormClosing handler)
        Me.Close()
        ' Εναλλακτικά, αν θέλεις να βεβαιωθείς ότι τερματίζει όλη η εφαρμογή:
        ' Application.Exit()
    End Sub

    Private Sub btnClearFileData_Click(sender As Object, e As EventArgs) Handles btnClearFileData.Click
        filePath = txtSaveFolder.Text & "\" & txtFileName.Text
        If filePath = "\" Then
            MsgBox("Επιλέξτε φάκελο και όνομα αρχείου για αποθήκευση δεδομένων.", MsgBoxStyle.Exclamation, "Προσοχή")
        Else

            ' Επιβεβαίωση
            If loggingEnabled Then
                Dim ans As DialogResult = MessageBox.Show("Υπάρχει ενεργή καταγραφή. Να σταματήσει και να καθαριστεί το αρχείο;", "Επιβεβαίωση", MessageBoxButtons.YesNo, MessageBoxIcon.Question)
                If ans = DialogResult.No Then Return
            End If

            Dim wasLogging As Boolean = loggingEnabled
            Dim portWasOpen As Boolean = False

            ' Σταμάτα καταγραφή και κλείσε θύρα προσωρινά
            loggingEnabled = False
            Try
                portWasOpen = (SerialPort1 IsNot Nothing AndAlso SerialPort1.IsOpen)
                If portWasOpen Then SerialPort1.Close()
            Catch
                ' αγνόησε σφάλματα στο κλείσιμο της θύρας
            End Try

            Try
                ' Αν θέλεις να διαγράψεις το αρχείο εντελώς:
                ' If File.Exists(filePath) Then File.Delete(filePath)

                ' Εδώ: αντικαθιστούμε το περιεχόμενο κρατώντας header
                Dim header As String = "t (s),x (cm),V (cm/s),a (cm/s^2)" & Environment.NewLine
                File.WriteAllText(filePath, header)

                txtData.AppendText("■ Το αρχείο καθαρίστηκε: " & filePath & Environment.NewLine)
            Catch ex As Exception
                MessageBox.Show("Σφάλμα κατά το καθάρισμα αρχείου: " & ex.Message, "Σφάλμα", MessageBoxButtons.OK, MessageBoxIcon.Error)
            Finally
                ' Προσπαθούμε να επαναφέρουμε τη θύρα και την κατάσταση καταγραφής
                Try
                    If portWasOpen Then SerialPort1.Open()
                Catch ex As Exception
                    MessageBox.Show("Δεν ήταν δυνατή η επαναφορά της σειριακής θύρας: " & ex.Message, "Προσοχή", MessageBoxButtons.OK, MessageBoxIcon.Warning)
                End Try
                loggingEnabled = wasLogging
            End Try

        End If




    End Sub
End Class
