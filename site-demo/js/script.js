let displayedContent;
let titles = document.querySelectorAll(".title");
let contents = document.querySelectorAll(".content-cards");
let iframes = document.querySelectorAll("iframe");
let iframeLinks = ["https://replit.com/@delai/ex1-pontos-cartesianos#main.c", 
                   "https://replit.com/@delai/ex2-catalogo-de-jogos#main.c",
                   "",
                   "https://replit.com/@delai/ex4-pilha-de-cartas#main.c",
                   "https://replit.com/@delai/ex5-big-numbers#main.c",
                   "https://replit.com/@delai/ex6-conta-bancaria#main.c",
                   "",
                   "https://replit.com/@delai/ex8-catalogo-de-jogos-ii#main.c"];

loadIframeContent(1);
showSelectedContent(1);
addClickEventToButtons();

function addClickEventToButtons() {
    let buttons = document.querySelectorAll("header li");

    for (let i=0; i<buttons.length; i++) {
        buttons[i].onclick = handleButtonClick;
        buttons[i].contentReference = i + 1;
    }
}

function handleButtonClick(event) {
    hideDisplayedContent();
    loadIframeContent(event.target.contentReference);
    showSelectedContent(event.target.contentReference);
}

function hideDisplayedContent() {
    iframes[displayedContent - 1].style.opacity = 0;
    titles[displayedContent - 1].style.opacity = 0;
    contents[displayedContent - 1].style.opacity = 0;

    setTimeout(() => {
        iframes[displayedContent - 1].style.display = "none";
        titles[displayedContent - 1].style.display = "none"
        contents[displayedContent - 1].style.display = "none";
    }, 400)
}

function loadIframeContent(selectedContent) {
    let iframe = iframes[selectedContent - 1];

    if (!iframe.wasLoaded) {
        iframe.src = iframeLinks[(selectedContent - 1)];
        iframe.wasLoaded = true;
    }
}

function showSelectedContent(selectedContent) {
    setTimeout(() => {
        iframes[selectedContent - 1].style.display = "block";
        titles[selectedContent - 1].style.display = "flex";
        contents[selectedContent - 1].style.display = "block";
    }, 450);

    setTimeout(() => {
        iframes[selectedContent - 1].style.opacity = 100;  
        titles[selectedContent - 1].style.opacity = 100;
        contents[selectedContent - 1].style.opacity = 100;  
    }, 500);

    setTimeout(() => {
        displayedContent = selectedContent;
    }, 550);
}