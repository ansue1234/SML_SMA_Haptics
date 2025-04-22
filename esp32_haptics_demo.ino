#include <WiFi.h>
#include <Arduino.h>
#include <ESPAsyncWebSrv.h>
#include <atomic>

const char *ssid = "iPhone";
const char *password = "potato4321";

AsyncWebServer server(80);

std::atomic<bool> trigger{false};

// SMA actuator configs
const int NUM_ACT = 4;
const int sma_pins[NUM_ACT] = {5, 16, 17, 18};  // w, a, s, d (up, left, down, right)
const float sma_duty_cycles[NUM_ACT] = {80.0, 80.0, 80.0, 80.0};
const int act_time = 300; // in millisec

// PWM Setup
const int sma_channels[NUM_ACT] = {0, 1, 2, 3};
const int PWM_FREQ = 1000;
const int PWM_RES = 16;
const int MAX_DUTY_CYCLE = (int)(pow(2, PWM_RES) - 1);

void setup() {

  // Setting up actuator
  for (int i = 0; i < NUM_ACT; i++) {
    ledcSetup(sma_channels[i], PWM_FREQ, PWM_RES);
    ledcAttachPin(sma_pins[i], sma_channels[i]);
  }
  
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println(WiFi.localIP());
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());

  server.on("/receiveData", HTTP_POST, [](AsyncWebServerRequest *request) {
    String data = request->arg("data");
  //  Serial.println("Received data: " + data);
    trigger.store(true);
    request->send(200, "text/plain", "Data received successfully");
  });

  server.begin();
}

void loop() {
  if (trigger.load()) {
    trigger_actuator();
    trigger.store(false);
  }
}

void trigger_actuator() {
  Serial.println("-----------------------Triggered----------------------");
  Serial.println("Starting Activation...");
  for (int i = 0; i < NUM_ACT; i++) {
    int raw_duty_cycle_val = compute_duty_value(sma_duty_cycles[i]);
    ledcWrite(sma_channels[i], raw_duty_cycle_val);
  }
  delay(act_time);
  for (int j = 0; j < NUM_ACT; j++) {
    ledcWrite(sma_channels[j], 0);
  }
  Serial.println("Ending Activation...");
  delay(2000);
}

int compute_duty_value(float percentage) {
  // (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min
  float duty_val = percentage * MAX_DUTY_CYCLE / 100;
  return duty_val;
}