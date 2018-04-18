using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace ArtClubWebApp.Controllers
{
    public class PicturesController : Controller
    {
        // GET: Pictures
        public ActionResult Index()
        {
            return View();
        }
    }
}