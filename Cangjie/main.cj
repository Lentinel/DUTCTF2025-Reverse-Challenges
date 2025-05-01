package chall_cj

import net.http.*
import std.time.*
import std.sync.*
import std.log.LogLevel
import encoding.base64.*

// 1. 构建 Server 实例
let server = ServerBuilder()
    .addr("127.0.0.1")
    .port(8080)
    .build()

func encrypt(data: String): String{
    let enc :Array<Byte> = [0xd5,0xde,0xd0,0xdc,0xe7,0xea,0xf4,0xf5,0xed,0xea,0xfe,0xd4,0xee,0xf8,0xfa,0xd0,0xd3,0xf0,0xfc,0xf4,0xfe,0xfc,0xf3,0xc8,0xf1,0xea,0xc5,0xfa,0xc3,0xe5,0xe6,0xe7,0xff,0xe8,0xfd,0x97,0xc3,0xc0,0xd2];
    let src = data.toArray()
    for (i in 0..enc.size) {
        if((src[i] ^ UInt8(0x80+i)) != enc[i]){
            return "wrong";
        }
    }
    return "right";

}

func startServer(): Unit {
    // 2. 注册请求处理逻辑
    server.distributor.register("/", {httpContext =>
        httpContext.responseBuilder.body(encrypt(httpContext.request.url.queryForm.get("A1_cE").getOrThrow()))
    })
    server.logger.level = OFF
    // 3. 启动服务
    server.serve()
}

// func startClient(): Unit {
//     // 1. 构建 client 实例
//     let client = ClientBuilder().build()
//     // 2. 发送 request
//     let response = client.get("http://127.0.0.1:${server.port}/?A1_cE=U_R_correct_but_Cangjie_is_a_xxx_I_4get")
//     // 3. 读取response body
//     let buffer = Array<Byte>(32, item: 0)
//     let length = response.body.read(buffer)
//     println(String.fromUtf8(buffer[..length]))
//     // 4. 关闭连接
//     client.close()
// }

main () {
	// 启动服务端
    let server: Future<Unit> = spawn {
        startServer()
    }
	
	// 阻塞当前运行的线程后再让客户端访问服务端，如无需要可去掉
    // sleep(Duration.second)
    // startClient()

	// 服务端运行中
    server.get()
    
}