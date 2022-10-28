using System;
using System.Globalization;
using System.Data;

public partial class Q2 : System.Web.UI.Page // HCJ edited class name
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
            string date1 = myHelpers.CleanInput(txtDate1.Text);
            string date2 = myHelpers.CleanInput(txtDate2.Text);

            //**************
            // HCJ: Q2
            //**************
            DataTable dtEnrolledCourses = myUniversityDB.getQ2(date1, date2);

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
                    myHelpers.ShowMessage(lblResultMessage, "No accounts were registered between " + date1 + " and " + date2 + ".");  // changed by HCJ
                }
            }
            else //An SQL error occurred.
            {
                myHelpers.ShowMessage(lblResultMessage, "*** There is an error in the SQL statement of Q2.");
            }
        }
    }

    protected void cvStudentId_ServerValidate(object source, System.Web.UI.WebControls.ServerValidateEventArgs args)
    {
        //**************
        // Input validation
        //**************
        string date1 = myHelpers.CleanInput(txtDate1.Text);
        string date2 = myHelpers.CleanInput(txtDate2.Text);
        string error_msg = "";

        // check that birth date must be properly formatted
        DateTime result = new DateTime();
        DateTime result2 = new DateTime();
        try
        {
            CultureInfo provider = CultureInfo.InvariantCulture;
            result = DateTime.ParseExact(date1 + " 02:00", "yyyy-MM-dd HH:mm", provider);
        } catch (FormatException){
            args.IsValid = false;
            error_msg += "Could not parse date1.\n";
        }

        try
        {
            CultureInfo provider = CultureInfo.InvariantCulture;
            result2 = DateTime.ParseExact(date2 + " 02:00", "yyyy-MM-dd HH:mm", provider);
        }
        catch (FormatException)
        {
            args.IsValid = false;
            error_msg += "Could not parse date2.\n";
        }

        if (error_msg == "" && DateTime.Compare(result, result2) > 0) { // only compare dates if both are valid
            args.IsValid = false;
            error_msg += "Date2 is earlier than Date1.\n";
        }

        if (args.IsValid == false)
        {
            myHelpers.ShowMessage(lblResultMessage, error_msg);
        }
    }
}