function openNav() {
    document.getElementById("Nav").style.width = "250px";
    document.getElementById("Main").style.marginLeft = "250px";
    document.getElementById("NavOverlay").style.backgroundColor = "rgba(0,0,0,0.4)";
    document.getElementById("NavOverlay").style.left = "250px"
    document.getElementById("NavOverlay").style.zIndex = "1"
}

function closeNav() {
    document.getElementById("Nav").style.width = "0px";
    document.getElementById("Main").style.marginLeft = "0px";
    document.getElementById("NavOverlay").style.backgroundColor = "rgba(0,0,0,0.0)";
    document.getElementById("NavOverlay").style.left = "0px"
    document.getElementById("NavOverlay").style.zIndex = "-1"
}
