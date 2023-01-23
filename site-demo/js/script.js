addClickEventToButtons();

function addClickEventToButtons(){
    let buttons = document.querySelectorAll("nav li");

    for (let i=0; i<buttons.length; i++){
        buttons[i].onclick = handleButtonClick;
        buttons[i].contentReference = "ex" + (i+1);
    }
}

function handleButtonClick(event){
    hideAllContents();
    showProperContent(event.target.contentReference);
}

function hideAllContents(){
    let contents = document.querySelectorAll(".content");
    let titles = document.querySelectorAll("h2");

    for (let i=0; i<contents.length; i++){
        contents[i].style.display = "none";
        titles[i].style.display = "none";
    }
}

function showProperContent(className){
    let content = document.getElementsByClassName(className);
    content[0].style.display = "flex";
    content[1].style.display = "inline-block";
}