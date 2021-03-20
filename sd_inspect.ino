/**
 * Simple test for the SD Card using an Arduino Uno R2.
 * This will do three things:
 * 1. Connect to card
 * 2. Get card type
 * 3. Check the volume size
 * 
 */
#include<SPI.h>
#include<SD.h>

// Globals, primarly PIN setup
const int CS_PIN = 8;
const int CD_PIN = 9;

// Primary SD Card object
Sd2Card card;
// SD Card volume object
SdVolume volume;

void setup() {
  // Setup serial output
  Serial.begin(9600);

  // Do not run until a Serial connection is established
  while(!Serial) {;}
  
  Serial.println("Checking for SD Card...");

  // Set up CD (Card Detect) to input mode
  pinMode(CD_PIN, INPUT);
  // wait for the CD to go high
  while(!digitalRead(CD_PIN)) {
    delay(250);
  }

  initCard();
  printCardType();
  getVolumeData();
}

void loop() {
  // put your main code here, to run repeatedly:

}

/**
 * Setup the SdCard object.
 */
void initCard() {
  Serial.println("Setting up the SD Card...");
  // init the card lib
  if(!card.init(SPI_HALF_SPEED, CS_PIN)) {
    Serial.println("Failed to init SD card!");
    Serial.println("Reinsert card and restart...");
    while(1);
  } else {
    Serial.println("Card detected, wiring looks good!");
  }
}

/**
 * Simple function for printing the SD card type.
 * Currently supports:
 * 1. SD1
 * 2. SD2
 * 3. SDHC
 */
void printCardType() {
  // Get card type
  Serial.print("SD Card type: ");
  switch(card.type()) {
    case SD_CARD_TYPE_SD1:
      Serial.println("SD1");
      break;
    case SD_CARD_TYPE_SD2:
      Serial.println("SD2");
      break;
    case SD_CARD_TYPE_SDHC:
      Serial.println("SDHC");
      break;
    default:
      Serial.println("UNKNOWN");
  }
}

/**
 * Run through the volume information in the SD card.  This inlcudes:
 * 1. Cluster count
 * 2. # blocks per cluster
 * 3. block count
 * 4. volume type
 * 5. volume in Kb
 * 6. volume in Mb
 * 7. volume in Gb
 * 8. List all files in volume
 */
void getVolumeData() {
  if(!volume.init(card)) {
    Serial.println("Card is not formatted to FAT16/32, can't enumerate volume");
    while(1);
  } else {
    // 1. Clusters
    Serial.print("Clusters: ");
    Serial.println(volume.clusterCount());
    // 2. number of blocks per cluster
    Serial.print("# blocks per cluster: ");
    Serial.println(volume.blocksPerCluster());
    // 3. Block count
    Serial.print("Total # blocks: ");
    Serial.println(volume.blocksPerCluster() * volume.clusterCount());
    // Volume size in 32 bit int
    uint32_t volumeSize;
    // 4. Volume in type
    Serial.print("Volume type is: FAT");
    Serial.println(volume.fatType(), DEC);
    // 5. volume in Kb
    volumeSize = volume.blocksPerCluster();
    volumeSize *= volume.clusterCount();
    // SD Card blocks are always 512 bytes (2 blocks are 1 KB)
    volumeSize /= 2;
    Serial.print("Volume size (Kb): ");
    Serial.println(volumeSize);
    // 6. volume in Mb
    volumeSize /= 1024;
    Serial.print("Volume size (Mb): ");
    Serial.println(volumeSize);
    // 6. volume in Gb
    Serial.print("Volume size (Gb): ");
    Serial.println((float)volumeSize/1024.0);
    // 8. List files
    Serial.println("File found on volume:");
    SdFile root;
    root.openRoot(volume);
    root.ls(LS_R | LS_DATE | LS_SIZE);
    // close the root
    root.close();
  }
}
