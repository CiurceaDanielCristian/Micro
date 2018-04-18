using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace ArtClubWebApp.Controllers
{
    public class MembersController : Controller
    {
        // GET: Members
        public ActionResult MembersList()
        {
            return View();
        }
    }
}