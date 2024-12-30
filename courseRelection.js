function scrolll() {
    const container = document.getElementById("scrollContent");
    container.scrollBy({
        left: -150, 
        behavior: "smooth"
    });
}

function scrollR() {
    const container = document.getElementById("scrollContent");
    container.scrollBy({
        left: 150, 
        behavior: "smooth"
    });
}