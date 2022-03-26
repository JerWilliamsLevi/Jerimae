// http request using javascript proof of concept
// Cecilia Delcamp
// Version 1 3/26/2022


// https://developer.mozilla.org/en-US/docs/Web/API/Fetch_API/Using_Fetch
// https://developer.mozilla.org/en-US/docs/Web/API/fetch

var buttonPressed;


// ----------------------------------------
// this checks for browser compatibility
//if ("serial" in navigator) {
  // The Web Serial API is supported.
  // window.alert("Web Serial API is supported");
//}
//else {
//    window.alert("Web Serial API not supported");
//}


// ------------------------------------------
// this sends the actual string. the 'buttonPressed'
// variable comes from the onclick() embedded within
// the html.
// could probably also be done with an event listener
async function http_get(buttonPressed) { 
    
    url = 'http://192.168.0.32:8224/' + buttonPressed;
    console.log(url); 
    fetch(url, { mode: 'no-cors' }) 
    .then(data => console.log(data));
    
    return true;
    
}
