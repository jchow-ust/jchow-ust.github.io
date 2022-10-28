using System;
using System.Globalization;
using System.Data;

public partial class Q5 : System.Web.UI.Page // HCJ edited class name
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
            string year = myHelpers.CleanInput(txtDate1.Text);

            //**************
            // HCJ: Q5
            //**************
            DataTable dtEnrolledCourses = myUniversityDB.getQ5(year);

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
                    myHelpers.ShowMessage(lblResultMessage, "No playlists do not contain products aired after " + year + ".");  // changed by HCJ
                }
            }
            else //An SQL error occurred.
            {
                myHelpers.ShowMessage(lblResultMessage, "*** There is an error in the SQL statement of Q5.");
            }
        }
    }

    protected void cvStudentId_ServerValidate(object source, System.Web.UI.WebControls.ServerValidateEventArgs args)
    {
        //**************
        // Input validation
        //**************
        string year = myHelpers.CleanInput(txtDate1.Text);
        string error_msg = "";

        int year_int = -1;
        try
        {
            year_int = Int32.Parse(year);
            if (year_int <= 0) {
                throw new Exception();
            }
        }
        catch (Exception)
        {
            args.IsValid = false;
            error_msg += "Please enter a non-negative integer year.\n";
        }

        if (args.IsValid && year.Length > 4)
        { // already reject empty
            args.IsValid = false;
            error_msg += "Year can be no more than 4 digits.\n";
        }

        if (args.IsValid == false)
        {
            myHelpers.ShowMessage(lblResultMessage, error_msg);
        }
    }
}