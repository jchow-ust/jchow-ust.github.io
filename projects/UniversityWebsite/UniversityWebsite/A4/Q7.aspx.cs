using System;
using System.Data;

public partial class Q7 : System.Web.UI.Page // HCJ edited class name
{
    UniversityDB myUniversityDB = new UniversityDB();
    Helpers myHelpers = new Helpers();

    protected void Page_Load(object sender, EventArgs e)
    {

    }

    protected void btnFindEnrolledCourses_Click(object sender, EventArgs e)
    {
        if (Page.IsValid)
        {
            // Hide the search result.
            lblResultMessage.Visible = false;
            lblResultMessage.Text = "";
            string username = myHelpers.CleanInput(txtStudentId.Text);

            //**************
            // HCJ: Q7
            //**************
            decimal val = myUniversityDB.getQ7values(username);
            if (val == 0) {
                myHelpers.ShowMessage(lblResultMessage, "This username does not exist in the DB.");
                return;
            }
            bool successDelete = myUniversityDB.doQ7_account(username);  // changed by HCJ

            if (successDelete==false)
            {
                myHelpers.ShowMessage(lblResultMessage, "Delete operation failed.");  // changed by HCJ
            }
            else 
            {
                myHelpers.ShowMessage(lblResultMessage, "The account with username '" + username + "' was deleted.");
            }
        }
    }
}