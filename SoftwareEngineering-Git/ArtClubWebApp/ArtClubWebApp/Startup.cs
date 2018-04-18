using Microsoft.Owin;
using Owin;

[assembly: OwinStartupAttribute(typeof(ArtClubWebApp.Startup))]
namespace ArtClubWebApp
{
    public partial class Startup
    {
        public void Configuration(IAppBuilder app)
        {
            ConfigureAuth(app);
        }
    }
}
