/*
    /////////////////////////////////////////////////////////////////////
// exp_coll.js - javascript for hide and show of scopes               //
// ver 1.0                                                          //
//-----------------------------------------------------------------//
//-----------------------------------------------------------------//
// Language:    C++, Visual Studio 2015                            //
// Platform:    Platform:      HP EliteBook, Windows 10            //
// Application: Project #3, CSE687 - Object Oriented Design, S2017 //
//  Author:        Manish Gupta, Syracuse University               //
//                 (315) 412-8140, magupta@syr.edu                 //
/////////////////////////////////////////////////////////////////////
/*
/*
* Package Operations:
* -------------------
* javascript for hide and show

* Maintenance History:
*---------------------
*ver 1.0 : 05 Apr 2017
* - first release
*/

var acc = document.getElementsByClassName("accordion");
var i;

for (i = 0; i < acc.length; i++) {
  acc[i].onclick = function() {
    this.classList.toggle("active");
    var panel = this.nextElementSibling;
    if (panel.style.maxHeight){
      panel.style.maxHeight = null;
    } else {
      panel.style.maxHeight = panel.scrollHeight + "500px";
    } 
  }
}