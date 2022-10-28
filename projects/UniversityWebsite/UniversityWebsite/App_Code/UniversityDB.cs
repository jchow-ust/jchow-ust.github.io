// CHOW Hau Cheung Jasper (20589533)
using Oracle.DataAccess.Client;
using System.Data;
using System;

/// <summary>
/// Student name: 
/// Student id: 
/// </summary>

public class UniversityDB
{
    OracleDBAccess myOracleDBAccess = new OracleDBAccess();
    private string sql;

    #region SQL statements for students
    // HW4 start by HCJ
    // assume no SQL injection (sureeee...)
    // TIPS TO REMEMBER
    // -- use + to concatenate strings and use single quotes for chars
    // -- not recommended to put single quotes around values for attributes that are numbers
    // -- never put single quotes around null

    // HW4 Q1 added by HCJ
    public DataTable getQ1(string desired_tag) {
        sql = "SELECT videoId, title FROM (SELECT videoId, title FROM Video INNER JOIN (SELECT videoId AS V FROM Movie) ON V = videoId) INNER JOIN (SELECT videoId AS S FROM Tags WHERE tag = '" +
            desired_tag + "') ON videoId = S";
        return myOracleDBAccess.GetData(sql);
    }

    // HW4 Q2 added by HCJ, need check date1 < date2
    public DataTable getQ2(string date1, string date2)
    {
        sql = "SELECT username FROM Account WHERE registrationDate >= TO_DATE('" + date1 +
            "', 'YYYY-MM-DD') AND registrationDate <= TO_DATE('" + date2 +
            "', 'YYYY-MM-DD')";
        return myOracleDBAccess.GetData(sql);
    }

    // HW4 Q3 added by HCJ
    public DataTable getQ3(string cast_member)
    {
        sql = "select videoId, title from(select VideoId, count(*) from Watches natural join Movie natural join Acts natural join CastMember where castName like '%" + cast_member +
            "%' group by VideoId having count(*) = (select max(watchCount) from(select VideoId, count(*) as watchCount from Watches natural join Movie natural join Acts natural join CastMember where castName like '%" + cast_member +
            "%' group by videoId))) natural join Video";
        return myOracleDBAccess.GetData(sql);
    }

    // HW4 Q4 added by HCJ
    public DataTable getQ4(int input_age)
    {
        sql = "SELECT username, AGE_TODAY FROM Account INNER JOIN (SELECT username U, TRUNC((TO_DATE('2022-05-01', 'YYYY-MM-DD') - birthDate) / 365.25) AS AGE_TODAY FROM Account) ON U = username WHERE(AGE_TODAY > " + input_age + ")";
        return myOracleDBAccess.GetData(sql);
    }

    // HW4 Q5 added by HCJ
    public DataTable getQ5(string input_year)
    {
        sql = "SELECT DISTINCT username, playListName FROM Playlist MINUS (SELECT DISTINCT username, playListName FROM Playlist INNER JOIN ((SELECT videoId V FROM Movie WHERE dateOfRelease >= TO_DATE('" + input_year.ToString() +
            "-01-01', 'YYYY-MM-DD')) UNION (SELECT videoId FROM TVShow WHERE dateOfRelease >= TO_DATE('" + input_year.ToString() +
            "-01-01', 'YYYY-MM-DD'))) ON V = videoId)";
        return myOracleDBAccess.GetData(sql);
    }

    // HW4 Q6 added by HCJ
    public bool doQ6_account(string username, string name, string email, string birthDate, string registrationDate)
    {
        sql = "INSERT INTO Account VALUES('" + username + "', '" + name + "', '" + email + "', TO_DATE('" + birthDate + "', 'YYYY-MM-DD'), TO_DATE('" + registrationDate + "', 'YYYY-MM-DD'))";
        return UpdateData(sql);
    }

    public bool doQ6_premium(string username)
    {
        sql = "INSERT INTO Premium VALUES('" + username + "')";
        return UpdateData(sql);
    }

    public bool doQ6_free(string username)
    {
        sql = "INSERT INTO Free VALUES('" + username + "')";
        return UpdateData(sql);
    }

    // HW4 Q7 added by HCJ
    // since we have on delete cascade, once we delete the record in Account, the record with same PK in Premium/Free shall also be deleted.
    public bool doQ7_account(string username)
    {
        sql = "DELETE FROM Account WHERE username = '" + username + "'";
        return UpdateData(sql);
    }

    // HW4 Q8 added by HCJ
    public DataTable getQ8()
    {
        sql = "SELECT * FROM Account";
        return myOracleDBAccess.GetData(sql);
    }

    // helper function for Q6 to determine unique values
    public decimal getQ6values(string username, string email)
    {
        sql = "SELECT count(*) FROM Account WHERE username='" + username + "' OR email='" + email + "'";
        return myOracleDBAccess.GetAggregateValue(sql);
    }

    // helper function for Q7 to determine unique values
    public decimal getQ7values(string username)
    {
        sql = "SELECT count(*) FROM Account WHERE username='" + username + "'";
        return myOracleDBAccess.GetAggregateValue(sql);
    }

    // end by HCJ

    public DataTable GetStudentRecord(string studentId)
    {
        //******************************************************************F
        // TODO 1: Used in SearchForStudent.aspx.cs                        *
        // Construct the SELECT statement to find the record (i.e., return *
        // all the attributes) of a student identified by a studentId.     *
        //******************************************************************
        sql = "select * from Student where studentId='" + studentId + "'";
        return myOracleDBAccess.GetData(sql);
    }

    public decimal StudentIdIsValid(string studentId)
    {
        //*******************************************************************
        // TODO 2: Use in EnrolledCourses.aspx.cs, EnrollsInCourses.aspx.cs *
        // Determine if the student id exists in the database.              *
        // Returns 0 - does not exist; 1 - exists; -1 - SQL error.          *
        //*******************************************************************
        sql = "select count(*) from Student where studentId='" + studentId + "'";
        return myOracleDBAccess.GetAggregateValue(sql);
    }

    public DataTable GetDepartmentStudentRecords(string departmentId)
    {
        //************************************************************************
        // TODO 3: Used in SearchStudentRecords.aspx.cs                          *
        // Construct the SELECT statement to find the id, last name, first name  *
        // and cga of the students in a department identified by a departmentId. *
        //************************************************************************
        sql = "select studentId, lastName, firstName, CGA from Student where departmentId='"
            + departmentId + "'";
        return myOracleDBAccess.GetData(sql);
    }

    public DataTable GetDepartments()
    {
        //*************************************************
        // TODO 4: Used in SearchStudentRecords.aspx.cs   *
        // Construct the SELECT statement to retrieve the *
        // department id and name of all departments.     *
        //*************************************************
        sql = "select departmentId, departmentName from Department";
        return myOracleDBAccess.GetData(sql);
    }

    #endregion SQL statements for students

    #region SQL statements for enrolling in courses
    public DataTable GetEnrolledCourses(string studentId)
    {
        //******************************************************************************
        // TODO 5: Used in EnrolledCourses.aspx.cs                                     *
        // Construct the SELECT statement to find the id, name, credits and instructor *
        // of the courses in which a student, identified by a studentiId, is enrolled. *
        //******************************************************************************
        sql = "select E.courseId, courseName, credits, instructor from EnrollsIn E, Course C " +
            "where E.courseId=C.courseId and studentId='" + studentId + "'";
        return myOracleDBAccess.GetData(sql);
    }

    public DataTable GetCoursesAvailableToEnroll(string studentId)
    {
        //*********************************************************************************
        // TODO 6: Used in EnrollInCourses.aspx.cs                                        *
        // Construct the SELECT statement to find the id, name, credits and instructor of *
        // the courses that a student, identified by a studentiId, is NOT enrolled in.    *
        //*********************************************************************************
        sql = "with temp (courseId) as ((select courseId from Course) minus "+
            "(select courseId from EnrollsIn where studentId='"+studentId+"')) "+
            "select T.courseId, courseName, credits, instructor from temp T, Course C "+
            "where T.courseId = C.courseId";
        return myOracleDBAccess.GetData(sql);
    }

    public bool EnrollInCourses(string studentId, string courseId)
    {
        //**********************************************************************************
        // TODO 7: Used in EnrollInCourses.aspx.cs                                         *
        // Construct the INSERT statement to enroll a student in his/her selected courses. *
        //**********************************************************************************
        sql = "insert into EnrollsIn values ('"+studentId+"', '"+courseId+"',null)";
        return UpdateData(sql);
    }

    #endregion SQL statement for enrolling in courses

    #region *** DO NOT CHANGE THE METHOD BELOW THIS LINE. IT IS NOT A TODO!!! ***!
    private bool UpdateData(string sql)
    {
        OracleTransaction trans = myOracleDBAccess.BeginTransaction();
        if (trans == null) { return false; }  // Error creating the transaction.
        if (myOracleDBAccess.SetData(sql, trans))
        { myOracleDBAccess.CommitTransaction(trans); return true; } // The update succeeded.
        else
        { myOracleDBAccess.DisposeTransaction(trans); return false; } // The update failed.
    }
    #endregion
}