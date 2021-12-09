# caro_game
Thiết kế giao thức:
- Cấu trúc playerInfo:
 + char username[]
 + int score;
 + int rank;
- Cấu trúc Player:
 + SOCKET s;
 + char IPAddress;
 + char portAddress;
 + playerInfo playerinfo;
 + bool isFree;
- Cấu trúc sessionInfo:
 + Player player1;
 + Player player2;
 + int a[][] = 0;
- Khuôn dạng thông điệp: OPCODE | LENGTH | PAYLOAD
  + Opcode: Mã thao tác(1 byte)
	1: Gửi lời thách đấu
	2: Chấp nhận thách đấu
	3: Từ chối thách đấu
	4: Truyền thông tin nước đi
	5: Báo kết quả ván đấu
	6: Báo lỗi
  + Length: kích thước trong payload(2 byte)
  + Payload: dữ liệu
	* Opcode = 1 và 2, 3, payload chứa tên tài khoản
	* Opcode = 4 va length > 0 thì payload chứa toạ độ đánh
	* Opcode = 4 và length = 0 tức là xin thua
	* Opcode = 5, payload chứa tên người chơi thắng. Payload rỗng thì ván cờ hoà
 	* Opcode = 6, payload = 1 nếu ng chơi bận, payload = 2 nếu người chơi có mức hạng không phù hợp
- Hoạt động của giao thức:
 + b1: client gửi thông điệp thách đấu với tên tài khoản nhận cho server
 + b2: server kiểm tra Tên người chơi, nếu ng chơi đang bận, gửi lại thông điệp với opcode = 5 và payload = 1 
nếu người chơi có mức hạng k phù hợp, gửi lại thông điệp với opcode = 5 và payload = 2
nếu kiểm tra đủ điều kiện, server gửi cho người chơi kia thông điệp opcode = 1 với payload là tên người gửi.
 + b3: người chơi từ chối thách đấu, client gửi server thông điệp opcode = 3 và payload tên người thách đấu.
Server gửi lại người thách đấu thông điệp opcode 3, payload tên người từ chối

Nếu người chơi đồng ý, client gửi server thông điệp opcode = 2 và payload tên người thách đấu.
Server gửi lại người thách đấu thông điệp opcode 2, payload tên người đồng ý. Đổi trạng thái isFree của 2 Player sang false. Tạo sessionInfo bao gồm 2 player trên. Trận đấu bắt đầu
 + b4: Ng chơi 1 bắt đầu trước, đánh một nước, socket 1 gửi thông điệp opcode 4, payload toạ độ nước đi tới server và đợi đến khi nhận thông điệp mới đánh tiếp. Server gửi opcode 4, payload toạ độ nước đi tới socket 2.
Ng chơi 2 bắt đầu sau, đợi nhận được thông điệp nước đi mới được đánh, và nhận đc thì đánh một nước và  cũng gửi thông điệp cùng loại
 + b5: server mỗi nước đi sẽ đánh dấu vào mảng a, a=1 tức là vị trí dc danh bởi ng chơi 1 và ngược lại. Đồng thời kiểm tra nước đi có thắng hay không. Không có thì tiếp tục truyền. Nếu có thì lập tức truyền thông điệp báo kết quả tới cả 2. Cập nhật điểm và hạng cho ng chơi.
 Hoặc nhận được thông điệp opcode 4, length 0 thì cũng báo kết quả và cập nhật điểm.
Sau đó sẽ xoá phiên