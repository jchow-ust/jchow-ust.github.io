using System;
using System.Data;

public partial class Q1 : System.Web.UI.Page // HCJ edited class name
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
            // Hide the search result.
            lblResultMessage.Visible = false;
            string studentId = myHelpers.CleanInput(txtStudentId.Text);

            //**************
            // HCJ: Q1 *
            //**************
            DataTable dtEnrolledCourses = myUniversityDB.getQ1(studentId);  // changed by HCJ

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
                    myHelpers.ShowMessage(lblResultMessage, "No movies with tag " + studentId + " exist");  // changed by HCJ
                }
            }
            else //An SQL error occurred.
            {
                myHelpers.ShowMessage(lblResultMessage, "*** There is an error in the SQL statement of Q1.");
            }
        }
    }
}