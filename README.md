# GOLF 2D
## Introduction:
- Đây là một game đơn giản được viết bằng ngôn ngữ C++ và SDL2
- ![ima](https://github.com/Ngtvu1752/Golf/assets/153152445/85365795-7fb0-49f6-98d1-48789248884c)
## Content:
- Player sẽ phải đánh quả bóng vào trúng lỗ để hoàn thành game.
- Số gậy người chơi đánh càng ít thì càng tốt.
## Technologies:
- _IDE_: Code::Block 20.03.
- _Thư viện_: SDL2
## How to play:
- Người chơi giữ chuột phải rồi kéo thả chuột để có thể đánh được bóng
- Điều chỉnh hướng chuột để bóng đi chính xác nhất
## Algorithsms
- Game sử dụng những công thức vật lý đối với vật chuyển động trong không gian Oxy để cho vật có thể di chuyển được
- Chúng ta lấy vận tốc của vật như sau:
   - Lấy vận tốc theo phương x và y bằng vị trí của chuột sau khi giữ và thả $$Vx = MouseX(ban đầu) - MouseX(lúc sau)$$
   - Ta sẽ tính khoảng cách của chuột khi nhấn giữ và khi thả bằng công thức:  $$M = \sqrt{(X - Xo)^2 + (Y - Yo)^2}$$. Khi đó M sẽ là vận tốc của bóng, 
   - Khi thả chuột, ta sẽ cập nhật vị trí mới của bóng theo Ox và Oy theo công thức: $$ Pos.X ban đầu = Pos.X ban đầu + V_x * deltatime. (với deltatime là thời gian mà vật chuyển động trong thời gian thực).
   - Công thức tỉ lệ của vận tốc thành phần và vận tốc của vật như sau:  $$\frac{V_x}{V_ox} = \frac{V_y}{V_oy} = \frac{V}{Vo} $$ Công thức trên sẽ cho ta chuyển đổi vận tốc về các vận tốc thành phần dễ dàng
   - Ta sẽ có một hằng số gia tốc để giảm vận tốc của quả bóng theo thời gian: $$\ V = V - a*t $$
- Việc kiểm tra va chạm của quả bóng là khá đơn giản, ta chỉ cẩn kiểm tra xem quả bóng va chạm theo phương X hay phương Y khi đó ta sẽ đổi hướng theo phương X hay phương Y của quả bóng.
   - ở đây ta sẽ dùng 2 biến là DirectionX và DirectionY đại diện cho chiều chuyển động của bóng với Direction = 1 tức là chiều dương và Direction = -1 tức là chiều âm.
### P/s: ý tưởng của game được dựa trên "polymars.itch.io/twini-golf"
