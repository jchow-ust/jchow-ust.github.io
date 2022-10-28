<%@ Page Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeFile="Q7.aspx.cs" Inherits="Q7" %> <%-- HCJ edited inherits --%>

<asp:Content ID="BodyContent" ContentPlaceHolderID="MainContent" runat="server">
    <div class="form-horizontal">
        <h4 class="col-md-offset-1"><span style="text-decoration: underline; color: #990000">Q7</span></h4> <%-- HCJ edited title text --%>
        <asp:Label ID="lblResultMessage" runat="server" Font-Bold="True" CssClass="label col-md-offset-1"></asp:Label>
        <hr />
        <div class="form-group">
            <asp:Label runat="server" AssociatedControlID="txtStudentId" CssClass="col-md-3 control-label">Username</asp:Label> <%-- HCJ edited label text--%>
            <div class="col-md-2">
                <asp:TextBox ID="txtStudentId" runat="server" MaxLength="20" CssClass="form-control input-sm" TextMode="SingleLine" ToolTip="Q7"></asp:TextBox> <%-- HCJ edited ToolTip, max tag size is 20, TextMode=Number -> SingleLine --%>
                <asp:RequiredFieldValidator runat="server" ErrorMessage="Please enter a valid username." ControlToValidate="txtStudentId" CssClass="text-danger" Display="Dynamic"></asp:RequiredFieldValidator>
            </div>
            <div class="col-md-2">
                <asp:Button ID="btnFindEnrolledCourses" runat="server" OnClick="btnFindEnrolledCourses_Click"
                    Text="Delete This User" CssClass="btn-sm" /> <%-- HCJ edited button text--%>
            </div>
        </div>
    </div>
</asp:Content>