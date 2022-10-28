<%@ Page Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeFile="Q3.aspx.cs" Inherits="Q3" %> <%-- HCJ edited inherits --%>

<asp:Content ID="BodyContent" ContentPlaceHolderID="MainContent" runat="server">
    <div class="form-horizontal">
        <h4 class="col-md-offset-1"><span style="text-decoration: underline; color: #990000">Q3</span></h4> <%-- HCJ edited title text --%>
        <asp:Label ID="lblResultMessage" runat="server" Font-Bold="True" CssClass="label col-md-offset-1"></asp:Label>
        <hr />
        <div class="form-group">
            <asp:Label runat="server" AssociatedControlID="txtStudentId" CssClass="col-md-3 control-label">Enter cast member name:</asp:Label> <%-- HCJ edited label text--%>
            <div class="col-md-2">
                <asp:TextBox ID="txtStudentId" runat="server" MaxLength="20" CssClass="form-control input-sm" TextMode="SingleLine" ToolTip="Q1"></asp:TextBox> <%-- HCJ edited ToolTip, max tag size is 20, TextMode=Number -> SingleLine --%>
                <asp:RequiredFieldValidator runat="server" ErrorMessage="Please enter a name." ControlToValidate="txtStudentId" CssClass="text-danger" Display="Dynamic"></asp:RequiredFieldValidator>
            </div>
            <div class="col-md-2">
                <asp:Button ID="btnFindEnrolledCourses" runat="server" OnClick="btnFindEnrolledCourses_Click"
                    Text="Find Movies" CssClass="btn-sm" /> <%-- HCJ edited button text--%>
            </div>
        </div>
        <asp:Panel ID="pnlEnrolledCourses" runat="server" Visible="False">
            <hr />
            <div class="form-group">
                <div class="col-md-offset-1 col-md-10">
                    <asp:GridView ID="gvEnrolledCourses" runat="server" BorderWidth="2px" CssClass="table-condensed" BorderStyle="Solid" 
                        Caption="<b>Most Watched Movies Featuring this Cast Member</b>" CaptionAlign="Top" CellPadding="3"></asp:GridView> <%-- HCJ edited result text caption --%>
                </div>
            </div>
        </asp:Panel>
    </div>
</asp:Content>