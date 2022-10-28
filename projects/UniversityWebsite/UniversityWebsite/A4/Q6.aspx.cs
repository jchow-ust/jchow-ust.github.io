using System;
using System.Globalization;
using System.Data;

public partial class Q6 : System.Web.UI.Page // HCJ edited class name
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
            lblResultMessage.Visible = false;
            lblResultMessage.Text = ""; // reset for next use
            string username = myHelpers.CleanInput(txtStudentId.Text);
            string name = myHelpers.CleanInput(txtName.Text);
            string email = myHelpers.CleanInput(txtEmail.Text);
            string birthDate = myHelpers.CleanInput(txtBirthDate.Text);
            string isPremium = myHelpers.CleanInput(txtIsPremium.Text);

            //**************
            // HCJ: Q6
            //**************
            string registrationDate = DateTime.UtcNow.Date.ToString("yyyy-MM-dd"); // get registration date in this format for SQL to use
            bool successAdd = myUniversityDB.doQ6_account(username, name, email, birthDate, registrationDate);  // changed by HCJ
            
            if (successAdd == true)
            {
                string zero = "0";
                string one = "1";
                bool successAddSubclass = false;
                if (isPremium.Equals(zero)) {
                    successAddSubclass = myUniversityDB.doQ6_free(username);  // changed by HCJ
                }
                if (isPremium.Equals(one)) {
                    successAddSubclass = myUniversityDB.doQ6_premium(username);  // changed by HCJ
                }
                myHelpers.ShowMessage(lblResultMessage, "User with username '" + username + "' was successfully added."); // assume if can add to Account, then can add to the subclass.
            }
            else
            {
                myHelpers.ShowMessage(lblResultMessage, "Failed to add user.");

            }
        }
    }

    protected void cvStudentId_ServerValidate(object source, System.Web.UI.WebControls.ServerValidateEventArgs args)
    {
        //**************
        // Input validation for all columns of Account
        //**************
        string username = myHelpers.CleanInput(txtStudentId.Text);
        string name = myHelpers.CleanInput(txtName.Text);
        string email = myHelpers.CleanInput(txtEmail.Text);
        string birthDate = myHelpers.CleanInput(txtBirthDate.Text);
        string isPremium = myHelpers.CleanInput(txtIsPremium.Text);

        string zero = "0";
        string one = "1";
        string error_msg = "";

        // check that isPremium must be either "0" or "1"
        if ((isPremium.Equals(zero) || isPremium.Equals(one)) == false)
        {
            args.IsValid = false;
            error_msg += "IsPremium field should be 0 or 1.\n";
        }

        // check that username must be unique
        // check that email must be unique
        decimal matches = myUniversityDB.getQ6values(username, email);
        if (matches > 0) {
            args.IsValid = false;
            error_msg += "Both email and username must be unique. Please go to Q8 page to make sure.\n";
        }

        // check that birth date must be properly formatted
        try
        {
            CultureInfo provider = CultureInfo.InvariantCulture;
            DateTime result = DateTime.ParseExact(birthDate + " 02:00", "yyyy-MM-dd HH:mm", provider);
        } catch (FormatException){
            args.IsValid = false;
            error_msg += "Could not parse birth date.\n";
        }

        if (args.IsValid == false)
        {
            myHelpers.ShowMessage(lblResultMessage, error_msg);
        }
    }
}