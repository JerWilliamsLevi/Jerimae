// serial connection proof of concept
// Cecilia Delcamp
// Version 1 3/9/2022

// uses https://web.dev/serial/
// uses https://developer.mozilla.org/en-US/docs/Web/API/SerialPort

// these can probably be declared within functions
// and passed, which may be better
var buttonPressed;
var port;

// ----------------------------------------
// this checks for browser compatibility
// compatible with Chrome 89+, tested in Chrome 99
// should be compatible with Edge as well
// NOT compatible with Internet Explorer, Firefox
if ("serial" in navigator) {
  // The Web Serial API is supported.
  // window.alert("Web Serial API is supported");
}
else {
    window.alert("Web Serial API not supported");
}


// ----------------------------------------
// this sets up the serial port. the baud rate needs
// to match the settings for the COM port. 9600 is
// a common default setting
async function promptUserForPort() {
    // you supposedly can set up filters so that the
    // user only sees the relevant COM ports. I have
    // not tested this.
    port = await navigator.serial.requestPort();
    await port.open({ baudRate: 9600 });
    if (port.writable) {
        console.log("port open");
    } else {
            console.log("error opening port");
    }   
    return true;
}

// ------------------------------------------
// this sends the actual string. the 'buttonPressed'
// variable comes from the onclick() embedded within
// the html.
// could probably also be done with an event listener
async function sendSerial(buttonPressed) { 
    
    // this checks if there is a port selected. it
    // should only ask the first time the browser is 
    // opened. after that it should just send the data
    if (!port) {
        await promptUserForPort();
    }
    
    // this builds a stream, locks it, and sends data
    const encoder = new TextEncoder();
    const writer = port.writable.getWriter();
    await writer.write(encoder.encode(buttonPressed));
    console.log("sent");
    await writer.releaseLock();
    console.log("released");

    return true;
    
}
