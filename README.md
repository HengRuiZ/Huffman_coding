Huffman编解码

1）内容：
利用 Huffman 编码进行通信可以大大提高信道的利用率，缩短信息传输时间，降低传输成本。但是，这要求在发送端通过一个编码系统对待传数据进行预先编码，在接收端进行解码。对于双工信道（即可以双向传输信息的信道），每端都需要一个完整的编/解码系统。

2）要求：
一个完整的huffman编解码系统应该具有以下功能：
初始化（Initialization）。从终端读入字符集大小n，以及n个字符和n个权值，建立Huffman 树，并将它存入fmTree 中。
编码（Encoding）。利用已经建好的Huffman树（如果不在内存，则应从文件hfmTree中读取），对文件ToBeTran中的正文进行编码，然后将结果存入文件CodeFile中。
解码（Decoding）。利用已经建立好的Huffman树将文件CodeFile中的代码进行解码，结果存入TextFile中。
打印代码文件（Print）。将文件CodeFile以紧凑的格式显示在终端上，每行 50个代码。同时将此字符形式的编码文件写入文件CodePrint中。
打印Huffman树（Tree Printing）。将已经在内存中的Huffman树以直观的形式（树或者凹入的形式）显示在终端上，同时将此字符形式的Huffman 树写入文件TreePrint中。
