🔹 1. Sự kiện cửa sổ (Window Events)
event.type	                                    Ý nghĩa
Event::Closed                                  	Người dùng nhấn nút đóng cửa sổ → nên gọi window.close()
Event::Resized                                 	Cửa sổ được thay đổi kích thước
Event::LostFocus                              	Cửa sổ mất focus (người dùng chuyển sang app khác)
Event::GainedFocus	                            Cửa sổ được focus trở lại
Event::TextEntered                             	Nhập ký tự (chuỗi Unicode)
🔹 2. Sự kiện bàn phím (Keyboard Events)
event.type	                                    Mô tả
Event::KeyPressed	                              Nhấn 1 phím (chỉ 1 lần khi nhấn)
Event::KeyReleased	                            Nhả phím
event.key.code	                                Xác định phím (vd: Keyboard::Up, Keyboard::A)

Ví dụ:

if(event.type == Event::KeyPressed){
    if(event.key.code == Keyboard::Space) { /* bắn */ }
}

🔹 3. Sự kiện chuột (Mouse Events)
event.type	                                                    Mô tả
Event::MouseButtonPressed	                                    Nhấn nút chuột
Event::MouseButtonReleased	                                  Nhả nút chuột
Event::MouseMoved                                           	Chuột di chuyển
Event::MouseWheelScrolled	                                    Cuộn bánh xe chuột

Ví dụ:

if(event.type == Event::MouseButtonPressed){
    if(event.mouseButton.button == Mouse::Left){
        int x = event.mouseButton.x;
        int y = event.mouseButton.y;
    }
}

🔹 4. Sự kiện joystick / gamepad
event.type	                                                  Mô tả
Event::JoystickButtonPressed	                             Nhấn nút joystick
Event::JoystickButtonReleased	                             Nhả nút joystick
Event::JoystickMoved	                                     Joystick di chuyển
🔹 5. Sự kiện thời gian thực

Không phải event trong pollEvent nhưng thường dùng cùng:

Keyboard::isKeyPressed(Keyboard::Up)                          → kiểm tra phím đang nhấn.

Mouse::isButtonPressed(Mouse::Left)                           → kiểm tra chuột đang nhấn.

🔹 Ghi nhớ nhanh

pollEvent(event)                          → lấy từng sự kiện từ hàng đợi.

Keyboard::isKeyPressed()                  → kiểm tra liên tục phím đang nhấn (real-time).

Mouse::getPosition(window)                → lấy vị trí chuột hiện tại.


