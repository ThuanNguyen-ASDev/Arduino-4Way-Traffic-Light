/*
 * MÔ HÌNH ĐÈN GIAO THÔNG NGÃ TƯ 4 TRỤ (2 CẶP ĐỐI XỨNG)
 * Board: Arduino Uno R3
 * LED 7 đoạn: Dương chung (Common Anode)
 */

// --- KHAI BÁO CHÂN ---
// 1. Chân LED 7 đoạn (a, b, c, d, e, f, g)
const int segPins[] = {2, 3, 4, 5, 6, 7, 8}; 

// 2. Chân Đèn Giao Thông - PHE 1 (Dọc)
const int green1 = 9;
const int yellow1 = 10;
const int red1 = 11;

// 3. Chân Đèn Giao Thông - PHE 2 (Ngang)
// Lưu ý: A0 được dùng như chân Digital số 14
const int green2 = 12;
const int yellow2 = 13;
const int red2 = A0; 

// --- MÃ HEX HIỂN THỊ SỐ 0-9 ---
// Mã này quy định các thanh sáng/tắt. 
// Với Dương chung: 0 là Sáng, 1 là Tắt -> Cần đảo ngược bit khi xuất.
const byte numbers[] = {
  0x3F, // 0
  0x06, // 1
  0x5B, // 2
  0x4F, // 3
  0x66, // 4
  0x6D, // 5
  0x7D, // 6
  0x07, // 7
  0x7F, // 8
  0x6F  // 9
};

void setup() {
  // Cấu hình chân LED 7 đoạn
  for (int i = 0; i < 7; i++) {
    pinMode(segPins[i], OUTPUT);
    digitalWrite(segPins[i], HIGH); // Tắt hết (Mặc định cho Dương chung)
  }
  
  // Cấu hình chân Đèn giao thông
  pinMode(green1, OUTPUT); pinMode(yellow1, OUTPUT); pinMode(red1, OUTPUT);
  pinMode(green2, OUTPUT); pinMode(yellow2, OUTPUT); pinMode(red2, OUTPUT);
}

// Hàm hiển thị số lên LED 7 đoạn (Đã xử lý Dương chung)
void displayNumber(int num) {
  if (num < 0 || num > 9) return; // Bảo vệ nếu số ngoài phạm vi
  
  byte segmentState = numbers[num];
  for (int i = 0; i < 7; i++) {
    // Logic: Lấy bit -> Đảo ngược (!) -> Xuất ra
    digitalWrite(segPins[i], !((segmentState >> i) & 1));
  }
}

// Hàm Điều Khiển Ngã Tư
// duration: Số giây đếm ngược
// phase: 1 (Phe 1 Xanh/Vàng), 2 (Phe 2 Xanh/Vàng)
// isYellow: true (Đèn vàng), false (Đèn xanh)
void trafficPhase(int duration, int activeGroup, bool isYellow) {
  
  // -- BƯỚC 1: SET TRẠNG THÁI ĐÈN --
  
  // Reset tất cả về tắt trước (để tránh chồng lấn màu)
  digitalWrite(green1, LOW); digitalWrite(yellow1, LOW); digitalWrite(red1, LOW);
  digitalWrite(green2, LOW); digitalWrite(yellow2, LOW); digitalWrite(red2, LOW);
  
  if (activeGroup == 1) { // PHE 1 ĐƯỢC ĐI
    digitalWrite(red2, HIGH); // Phe 2 phải Đỏ
    if (isYellow) digitalWrite(yellow1, HIGH);
    else          digitalWrite(green1, HIGH);
  } 
  else { // PHE 2 ĐƯỢC ĐI
    digitalWrite(red1, HIGH); // Phe 1 phải Đỏ
    if (isYellow) digitalWrite(yellow2, HIGH);
    else          digitalWrite(green2, HIGH);
  }

  // -- BƯỚC 2: ĐẾM NGƯỢC --
  for (int i = duration; i > 0; i--) {
    displayNumber(i);
    delay(1000);
  }
}

void loop() {
  // KỊCH BẢN CHẠY:
  
  // 1. Phe 1: XANH (5s) | Phe 2: ĐỎ
  trafficPhase(5, 1, false);
  
  // 2. Phe 1: VÀNG (2s) | Phe 2: ĐỎ
  trafficPhase(2, 1, true);
  
  // 3. Phe 2: XANH (5s) | Phe 1: ĐỎ
  trafficPhase(5, 2, false);
  
  // 4. Phe 2: VÀNG (2s) | Phe 1: ĐỎ
  trafficPhase(2, 2, true);
}