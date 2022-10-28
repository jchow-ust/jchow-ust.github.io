<%@ Page Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeFile="Q4.aspx.cs" Inherits="Q4" %> <%-- HCJ edited inherits --%>

<asp:Content ID="BodyContent" ContentPlaceHolderID="MainContent" runat="server">
    <div class="form-horizontal">
        <h4 class="col-md-offset-1"><span style="text-decoration: underline; color: #990000">Q4</span></h4> <%-- HCJ edited title text --%>
        <asp:Label ID="lblResultMessage" runat="server" Font-Bold="True" CssClass="label col-md-offset-1"></asp:Label>
        <hr />
        <div class="form-group">
            <asp:Label runat="server" AssociatedControlID="txtDate1" CssClass="col-md-3 control-label">Age:</asp:Label> <%-- HCJ edited label text--%>
            <div class="col-md-2">
                <asp:TextBox ID="txtDate1" runat="server" MaxLength="7" CssClass="form-control input-sm" TextMode="SingleLine" ToolTip="Q2"></asp:TextBox> <%-- HCJ edited ToolTip, max tag size is 20, TextMode=Number -> SingleLine --%>
                <asp:RequiredFieldValidator runat="server" ErrorMessage="Please enter a number (age)." ControlToValidate="txtDate1" CssClass="text-danger" Display="Dynamic"></asp:RequiredFieldValidator>
                <%-- HCJ removed RegularExpressionValidator --%>
                <asp:CustomValidator ID="cvStudentId" runat="server" ControlToValidate="txtDate1" CssClass="text-danger" Display="Dynamic" EnableClientScript="False" OnServerValidate="cvStudentId_ServerValidate" Visible="True"></asp:CustomValidator>
            </div>
        </div>
        <div class="form-group">
            <div class="col-md-2">
                <asp:Button ID="Button5" runat="server" OnClick="btnFindEnrolledCourses_Click"
                    Text="Find Accounts" CssClass="btn-sm" /> <%-- HCJ edited button text--%>
            </div>
        </div>
        <asp:Panel ID="pnlEnrolledCourses" runat="server" Visible="False">
            <hr />
            <div class="form-group">
                <div class="col-md-offset-1 col-md-10">
                    <asp:GridView ID="gvEnrolledCourses" runat="server" BorderWidth="2px" CssClass="table-condensed" BorderStyle="Solid" 
                        Caption="<b>Accounts With Owners Older Than This Age</b>" CaptionAlign="Top" CellPadding="3"></asp:GridView> <%-- HCJ edited result text caption --%>
                </div>
            </div>
        </asp:Panel>
    </div>
</asp:Content>