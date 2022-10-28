<%@ Page Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeFile="Q8.aspx.cs" Inherits="Q8" %> <%-- HCJ edited inherits --%>

<asp:Content ID="BodyContent" ContentPlaceHolderID="MainContent" runat="server">
    <div class="form-horizontal">
        <h4 class="col-md-offset-1"><span style="text-decoration: underline; color: #990000">Q8</span></h4> <%-- HCJ edited title text --%>
        <asp:Label ID="lblResultMessage" runat="server" Font-Bold="True" CssClass="label col-md-offset-1"></asp:Label>
        <hr />
        <div class="form-group">
            <div class="col-md-2">
                <asp:Button ID="btnFindEnrolledCourses" runat="server" OnClick="btnFindEnrolledCourses_Click"
                    Text="Display All Users" CssClass="btn-sm" /> <%-- HCJ edited button text--%>
            </div>
        </div>
        <asp:Panel ID="pnlEnrolledCourses" runat="server" Visible="False">
            <hr />
            <div class="form-group">
                <div class="col-md-offset-1 col-md-10">
                    <asp:GridView ID="gvEnrolledCourses" runat="server" BorderWidth="2px" CssClass="table-condensed" BorderStyle="Solid" 
                        Caption="<b>List of Users</b>" CaptionAlign="Top" CellPadding="3"></asp:GridView> <%-- HCJ edited result text caption --%>
                </div>
            </div>
        </asp:Panel>
    </div>
</asp:Content>