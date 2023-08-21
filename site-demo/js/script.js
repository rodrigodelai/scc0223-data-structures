let displayedContent;

const titles = document.querySelectorAll(".title");
const contents = document.querySelectorAll(".content-cards");
const iframes = document.querySelectorAll("iframe");
const iframeLinks = ["https://replit.com/@delai/ex1-pontos-cartesianos#main.c", 
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
addClickEventToFooter();

function addClickEventToButtons() {
    const buttons = document.querySelectorAll("header li");

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
    const iframe = iframes[selectedContent - 1];

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

function addClickEventToFooter() {
    const footer = document.querySelector("footer");
    const dialog = document.querySelector("dialog");
    const closeButton = document.querySelector("footer button");

    footer.addEventListener("click", () => {showModal(footer, dialog)});

    closeButton.addEventListener("click", () => {closeModal(footer, dialog)});

    document.body.addEventListener("keydown", (event) => {
        if (event.key == "Escape") 
        closeModal(footer, dialog);
    });
}

function showModal(footer, dialog) {
    if (!footer.showingModal) {
        dialog.showModal();
        footer.showingModal = true;
        document.querySelector("input").focus();
    }
}

function closeModal(footer, dialog) {
    setTimeout(() => {
        dialog.close();
        footer.showingModal = false;
    });
}

function closeForm() {
    const footer = document.querySelector("footer");
    const dialog = document.querySelector("dialog");
    closeModal(footer, dialog);
}