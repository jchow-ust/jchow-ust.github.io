using System;
using System.Globalization;
using System.Data;

public partial class Q4 : System.Web.UI.Page // HCJ edited class name
{
    UniversityDB myUniversityDB = new UniversityDB();
    Helpers myHelpers = new Helpers();

    protected void Page_Load(object sender, EventArgs e)
    {

    }

    protected void btnFindEnrolledCourses_Click(object sender, EventArgs e)
    {
        pnlEnrolledCourses.Visible = false;
        if (Page.IsValid)
        {
            lblResultMessage.Visible = false;
            lblResultMessage.Text = ""; // reset for next use
            string age = myHelpers.CleanInput(txtDate1.Text);

            //**************
            // HCJ: Q4
            //**************
            DataTable dtEnrolledCourses = myUniversityDB.getQ4(Int32.Parse(age));

            // Show the enrolled courses if the query result is not null and something was retrieved.
            if (dtEnrolledCourses != null)
            {
                if (dtEnrolledCourses.Rows.Count != 0)
                {
                    gvEnrolledCourses.DataSource = dtEnrolledCourses;
                    gvEnrolledCourses.DataBind();
                    pnlEnrolledCourses.Visible = true;
                }
                else // Display a no result message.
                {
                    myHelpers.ShowMessage(lblResultMessage, "No accounts have owners whose age > " + age + ".");  // changed by HCJ
                }
            }
            else //An SQL error occurred.
            {
                myHelpers.ShowMessage(lblResultMessage, "*** There is an error in the SQL statement of Q4.");
            }
        }
    }

    protected void cvStudentId_ServerValidate(object source, System.Web.UI.WebControls.ServerValidateEventArgs args)
    {
        //**************
        // Input validation
        //**************
        string age_str = myHelpers.CleanInput(txtDate1.Text);
        string error_msg = "";
        int age = -1;
        try {
            age = Int32.Parse(age_str);
        } catch (Exception) {
            args.IsValid = false;
            error_msg += "Please enter an integer age.\n";
        }

        if (age < 0) {
            args.IsValid = false;
            error_msg += "Please enter a non-negative integer.\n";
        }

        if (args.IsValid == false)
        {
            myHelpers.ShowMessage(lblResultMessage, error_msg);
        }
    }
}