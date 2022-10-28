<%@ Page Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeFile="Q6.aspx.cs" Inherits="Q6" %> <%-- HCJ edited inherits --%>

<asp:Content ID="BodyContent" ContentPlaceHolderID="MainContent" runat="server">
    <div class="form-horizontal">
        <h4 class="col-md-offset-1"><span style="text-decoration: underline; color: #990000">Q6</span></h4> <%-- HCJ edited title text --%>
        <asp:Label ID="lblResultMessage" runat="server" Font-Bold="True" CssClass="label col-md-offset-1"></asp:Label>
        <hr />
        <div class="form-group">
            <asp:Label runat="server" AssociatedControlID="txtStudentId" CssClass="col-md-3 control-label">Username:</asp:Label> <%-- HCJ edited label text--%>
            <div class="col-md-2">
                <asp:TextBox ID="txtStudentId" runat="server" MaxLength="20" CssClass="form-control input-sm" TextMode="SingleLine" ToolTip="Q6"></asp:TextBox> <%-- HCJ edited ToolTip, max tag size is 20, TextMode=Number -> SingleLine --%>
                <asp:RequiredFieldValidator runat="server" ErrorMessage="Please enter a valid username." ControlToValidate="txtStudentId" CssClass="text-danger" Display="Dynamic"></asp:RequiredFieldValidator>
                <%-- HCJ removed RegularExpressionValidator --%>
                <asp:CustomValidator ID="cvStudentId" runat="server" ControlToValidate="txtStudentId" CssClass="text-danger" Display="Dynamic" EnableClientScript="False" OnServerValidate="cvStudentId_ServerValidate" Visible="True"></asp:CustomValidator>
            </div>
        </div>
        <div class="form-group">
            <asp:Label runat="server" AssociatedControlID="txtName" CssClass="col-md-3 control-label">Name:</asp:Label> <%-- HCJ edited label text--%>
            <div class="col-md-2">
                <asp:TextBox ID="txtName" runat="server" MaxLength="40" CssClass="form-control input-sm" TextMode="SingleLine" ToolTip="Q6"></asp:TextBox> <%-- HCJ edited ToolTip, max tag size is 20, TextMode=Number -> SingleLine --%>
                <asp:RequiredFieldValidator runat="server" ErrorMessage="Please enter a valid name." ControlToValidate="txtName" CssClass="text-danger" Display="Dynamic"></asp:RequiredFieldValidator>
            </div>
        </div>
        <div class="form-group">
            <asp:Label runat="server" AssociatedControlID="txtEmail" CssClass="col-md-3 control-label">Email Address:</asp:Label> <%-- HCJ edited label text--%>
            <div class="col-md-2">
                <asp:TextBox ID="txtEmail" runat="server" MaxLength="50" CssClass="form-control input-sm" TextMode="SingleLine" ToolTip="Q6"></asp:TextBox> <%-- HCJ edited ToolTip, max tag size is 20, TextMode=Number -> SingleLine --%>
                <asp:RequiredFieldValidator runat="server" ErrorMessage="Please enter a valid email." ControlToValidate="txtEmail" CssClass="text-danger" Display="Dynamic"></asp:RequiredFieldValidator>
            </div>
        </div>
        <div class="form-group">
            <asp:Label runat="server" AssociatedControlID="txtBirthDate" CssClass="col-md-3 control-label">Birth Date (Enter as YYYY-MM-DD):</asp:Label> <%-- HCJ edited label text--%>
            <div class="col-md-2">
                <asp:TextBox ID="txtBirthDate" runat="server" MaxLength="10" CssClass="form-control input-sm" TextMode="SingleLine" ToolTip="Q6"></asp:TextBox> <%-- HCJ edited ToolTip, max tag size is 20, TextMode=Number -> SingleLine --%>
                <asp:RequiredFieldValidator runat="server" ErrorMessage="Please enter a valid birth date." ControlToValidate="txtBirthDate" CssClass="text-danger" Display="Dynamic"></asp:RequiredFieldValidator>
            </div>
        </div>
        <div class="form-group">
            <asp:Label runat="server" AssociatedControlID="txtIsPremium" CssClass="col-md-3 control-label">Is Premium (enter 0 or 1):</asp:Label> <%-- HCJ edited label text--%>
            <div class="col-md-2">
                <asp:TextBox ID="txtIsPremium" runat="server" MaxLength="1" CssClass="form-control input-sm" TextMode="SingleLine" ToolTip="Q6"></asp:TextBox> <%-- HCJ edited ToolTip, max tag size is 20, TextMode=Number -> SingleLine --%>
                <asp:RequiredFieldValidator runat="server" ErrorMessage="Please enter whether this account is premium or not (0 or 1)." ControlToValidate="txtIsPremium" CssClass="text-danger" Display="Dynamic"></asp:RequiredFieldValidator>
            </div>
        </div>
        <div class="form-group">
            <div class="col-md-2">
                <asp:Button ID="Button5" runat="server" OnClick="btnFindEnrolledCourses_Click"
                    Text="Add User" CssClass="btn-sm" /> <%-- HCJ edited button text--%>
            </div>
        </div>
    </div>
</asp:Content>