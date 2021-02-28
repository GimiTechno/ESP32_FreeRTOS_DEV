#include "app_ota.h"
#include "app_wifi.h"
#include "app_ble.h"

extern BluetoothSerial SerialBT;

const char* p_mdns_host = "esp32";
extern const char* p_ssid;
extern const char* p_password;

static WebServer s_webserver(__WEBSERVER_PORT__);

const char* loginIndex =
    "<form name='loginForm'>"
        "<table width='50%' bgcolor='37C924' align='center'>"
            "<tr>"
                "<td colspan=2>"
                    "<center><font size=4><b>ESP32 OTA Update(F/W REV.0.11)</b></font></center>"
                    "<br>"
                "</td>"
                "<br>"
                "<br>"
            "</tr>"
            "<td>User:</td>"
            "<td><input type='text' size=25 name='userid'><br></td>"
            "</tr>"
            "<br>"
            "<br>"
            "<tr>"
                "<td>Password:</td>"
                "<td><input type='Password' size=25 name='pwd'><br></td>"
                "<br>"
                "<br>"
            "</tr>"
            "<tr>"
                "<td><input type='submit' onclick='check(this.form)' value='Login'></td>"
            "</tr>"
        "</table>"
    "</form>"
    "<script>"
        "function check(form)"
        "{"
        "if(form.userid.value=='admin' && form.pwd.value=='admin')"
        "{"
        "window.open('/serverIndex')"
        "}"
        "else"
        "{"
        " alert('Error Password or Username')/*displays error message*/"
        "}"
        "}"
    "</script>";

/*
 * Server Index Page
 */
const char* serverIndex = 
    "<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script>"
    "<form method='POST' action='#' enctype='multipart/form-data' id='upload_form'>"
    "<div id='prga'>OTA Update (F/W = *.bin) </div>"
    "<br>"
    "<input type='file' name='update'>"
            "<input type='submit' value='OTA Update'>"
        "</form>"
    "<div id='prg'>Progress: 0%</div>"
    "<script>"
    "$('form').submit(function(e){"
    "e.preventDefault();"
    "var form = $('#upload_form')[0];"
    "var data = new FormData(form);"
    " $.ajax({"
    "url: '/update',"
    "type: 'POST',"
    "data: data,"
    "contentType: false,"
    "processData:false,"
    "xhr: function() {"
    "var xhr = new window.XMLHttpRequest();"
    "xhr.upload.addEventListener('progress', function(evt) {"
    "if (evt.lengthComputable) {"
    "var per = evt.loaded / evt.total;"
    "$('#prg').html('progress: ' + Math.round(per*100) + '%');"
    "}"
    "}, false);"
    "return xhr;"
    "},"
    "success:function(d, s) {"
    "console.log('success!')" 
    "},"
    "error: function (a, b, c) {"
    "}"
    "});"
    "});"
    "</script>";

void APP_OTA_Init(void)
{
    /*use mdns for p_mdns_host name resolution*/
    if (!MDNS.begin(p_mdns_host)) { //http://esp32.local
        Serial.println("Error setting up MDNS responder!");
        while (1) {
        delay(1000);
        }
    }
    SerialBT.printf("OTA WEB Login OK\n");
    Serial.printf("OTA WEB Login OK\n");
    Serial.println("mDNS responder started");
    /*return index page which is stored in serverIndex */
    s_webserver.on("/", HTTP_GET, []() {
        s_webserver.sendHeader("Connection", "close");
        s_webserver.send(200, "text/html", loginIndex);
    });
    s_webserver.on("/serverIndex", HTTP_GET, []() {
        s_webserver.sendHeader("Connection", "close");
        s_webserver.send(200, "text/html", serverIndex);
    });
    /*handling uploading firmware file */
    s_webserver.on("/update", HTTP_POST, []() {
        s_webserver.sendHeader("Connection", "close");
        s_webserver.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
        ESP.restart();
    }, []() {
        HTTPUpload& upload = s_webserver.upload();
        if (upload.status == UPLOAD_FILE_START) {
            SerialBT.printf("OTA Update F/W: %s\n", upload.filename.c_str());
            Serial.printf("OTA Update F/W: %s\n", upload.filename.c_str());
            if (!Update.begin(UPDATE_SIZE_UNKNOWN)) { //start with max available size
                Update.printError(Serial);
            }
        } else if (upload.status == UPLOAD_FILE_WRITE) {
            /* flashing firmware to ESP*/
            if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
                Update.printError(Serial);
            }
        } else if (upload.status == UPLOAD_FILE_END) {
            if (Update.end(true)) { //true to set the size to the current progress
                SerialBT.printf("OTA Update : Success (TotalSize = %uByte)\nRebooting...\n", upload.totalSize);
                Serial.printf("OTA Update : Success (TotalSize = %uByte)\nRebooting...\n", upload.totalSize);
            } else {
                Update.printError(Serial);
            }
        }
    });
    s_webserver.begin();
}

void APP_OTA_Req_Catch(void)
{
    s_webserver.handleClient();
    delay(1);
}
