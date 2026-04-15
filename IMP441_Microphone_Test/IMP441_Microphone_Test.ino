#include <driver/i2s.h>

#define I2S_WS 25
#define I2S_SD 33
#define I2S_SCK 26
#define I2S_PORT I2S_NUM_0

// -------- I2S SETUP --------
void setupI2S() {
  const i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = 16000,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_STAND_I2S,
    .intr_alloc_flags = 0,
    .dma_buf_count = 8,
    .dma_buf_len = 16,
    .use_apll = false
  };

  const i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_SCK,
    .ws_io_num = I2S_WS,
    .data_out_num = I2S_PIN_NO_CHANGE,
    .data_in_num = I2S_SD
  };

  i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_PORT, &pin_config);
}

// -------- GET SOUND LEVEL --------
int getSoundLevel() {
  int32_t sample = 0;
  size_t bytes_read;

  long sum = 0;
  int samples = 100;

  for (int i = 0; i < samples; i++) {
    i2s_read(I2S_PORT, &sample, sizeof(sample), &bytes_read, portMAX_DELAY);

    sample = sample >> 14;   // Align data
    sum += abs(sample);
  }

  int avg = sum / samples;

  // Map to 0–100 scale (adjust if needed)
  int level = map(avg, 0, 3000, 0, 100);

  // Limit range
  level = constrain(level, 0, 100);

  return level;
}

// -------- SETUP --------
void setup() {
  Serial.begin(115200);
  setupI2S();
}

// -------- LOOP --------
void loop() {
  int level = getSoundLevel();

  String status;

  if (level < 10) status = "SILENT";
  else if (level < 30) status = "LOW";
  else if (level < 70) status = "MEDIUM";
  else status = "LOUD";

  Serial.print("Level: ");
  Serial.print(level);
  Serial.print("%  |  ");
  Serial.println(status);

  delay(200);
}