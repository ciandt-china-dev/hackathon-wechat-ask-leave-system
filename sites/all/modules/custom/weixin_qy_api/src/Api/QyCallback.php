<?php
/**
 * @file
 * 微信企业号开发(回调模式)
 */
namespace Drupal\weixin_qy_api\Api;

use Drupal\weixin_qy_api\Decryption\WXBizMsgCrypt;

/**
 * Class QyCallback
 *
 * @reference
 *   http://qydev.weixin.qq.com/wiki/index.php?title=回调模式
 */
class QyCallback {
  protected $corpID;
  protected $secret;
  protected $devModeToken;
  protected $devModeencodingAESKey;
  protected $approvalWechatTagName;
  protected $wxcpt;

  public function __construct() {
    $this->corpID = variable_get('enterprise_wechat_corp_id');
    $this->secret = variable_get('enterprise_wechat_secret');
    $this->devModeToken = variable_get('enterprise_wechat_dev_mode_token');
    $this->devModeencodingAESKey = variable_get('enterprise_wechat_dev_mode_encoding_aes_key');
    $this->approvalWechatTagName = variable_get('vacation_approver_wechat_tag_name');
    $this->wxcpt = new WXBizMsgCrypt($this->devModeToken, $this->devModeencodingAESKey, $this->corpID);
  }

  /*
    ------------使用示例一：验证回调URL---------------
    *企业开启回调模式时，企业号会向验证url发送一个get请求
    假设点击验证时，企业收到类似请求：
    * GET /cgi-bin/wxpush?msg_signature=5c45ff5e21c57e6ad56bac8758b79b1d9ac89fd3&timestamp=1409659589&nonce=263014780&echostr=P9nAzCzyDtyTWESHep1vC5X9xho%2FqYX3Zpb4yKa9SKld1DsH3Iyt3tP3zNdtp%2B4RPcs8TgAE7OaBO%2BFZXvnaqQ%3D%3D
    * HTTP/1.1 Host: qy.weixin.qq.com

    接收到该请求时，企业应
    1.解析出Get请求的参数，包括消息体 </xml>

  为了将此段明文回复给用户，企业应：
  1.自己生成时间时间戳(timestamp),随机数字串(nonce)以便生成消息体签名，也可以直接用从公众平台的post url上解析出的对应值。
  2.将明文加密得到密文。
  3.用密文，步骤1生成的timestamp,nonce和企业在公众平台设定的token生成消息体签名。
  4.将密文，消息体签名，时间戳，随机数字串拼接成xml格式的字符串，发送给企业号。
  以上2，3，4步可以用公众平台提供的库函数EncryptMsg来实现。
  签名(msg_signature)，时间戳(timestamp)，随机数字串(nonce)以及公众平台推送过来的随机加密字符串(echostr),
    这一步注意作URL解码。
    2.验证消息体签名的正确性
    3. 解密出echostr原文，将原文当作Get请求的response，返回给公众平台
    第2，3步可以用公众平台提供的库函数VerifyURL来实现。
    */
  public function validateCallbackUrl() {
    $msg_signature = urldecode($_GET['msg_signature']);
    $timestamp = urldecode($_GET['timestamp']);
    $nonce = urldecode($_GET['nonce']);
    $echostr = urldecode($_GET['echostr']);

    // 需要返回的明文
    $sEchoStr = "";
    $errCode = $this->wxcpt->VerifyURL($msg_signature, $timestamp, $nonce, $echostr, $sEchoStr);
    if ($errCode == 0) {
      // 验证URL成功，将sEchoStr返回
      echo $echostr;
    }
    else {
      echo $echostr;
      //print("ERR: " . $errCode . "\n\n");
    }
  }

  /*
------------使用示例二：对用户回复的消息解密---------------
用户回复消息或者点击事件响应时，企业会收到回调消息，此消息是经过公众平台加密之后的密文以post形式发送给企业，密文格式请参考官方文档
假设企业收到公众平台的回调消息如下：
POST /cgi-bin/wxpush? msg_signature=477715d11cdb4164915debcba66cb864d751f3e6&timestamp=1409659813&nonce=1372623149 HTTP/1.1
Host: qy.weixin.qq.com
Content-Length: 613
<xml>
<ToUserName><![CDATA[wx5823bf96d3bd56c7]]></ToUserName><Encrypt><![CDATA[RypEvHKD8QQKFhvQ6QleEB4J58tiPdvo+rtK1I9qca6aM/wvqnLSV5zEPeusUiX5L5X/0lWfrf0QADHHhGd3QczcdCUpj911L3vg3W/sYYvuJTs3TUUkSUXxaccAS0qhxchrRYt66wiSpGLYL42aM6A8dTT+6k4aSknmPj48kzJs8qLjvd4Xgpue06DOdnLxAUHzM6+kDZ+HMZfJYuR+LtwGc2hgf5gsijff0ekUNXZiqATP7PF5mZxZ3Izoun1s4zG4LUMnvw2r+KqCKIw+3IQH03v+BCA9nMELNqbSf6tiWSrXJB3LAVGUcallcrw8V2t9EL4EhzJWrQUax5wLVMNS0+rUPA3k22Ncx4XXZS9o0MBH27Bo6BpNelZpS+/uh9KsNlY6bHCmJU9p8g7m3fVKn28H3KDYA5Pl/T8Z1ptDAVe0lXdQ2YoyyH2uyPIGHBZZIs2pDBS8R07+qN+E7Q==]]></Encrypt>
<AgentID><![CDATA[218]]></AgentID>
</xml>

企业收到post请求之后应该
1.解析出url上的参数，包括消息体签名(msg_signature)，时间戳(timestamp)以及随机数字串(nonce)
2.验证消息体签名的正确性。
3.将post请求的数据进行xml解析，并将<Encrypt>标签的内容进行解密，解密出来的明文即是用户回复消息的明文，明文格式请参考官方文档
第2，3步可以用公众平台提供的库函数DecryptMsg来实现。
*/
//  public function decodeMessage() {
//    $msg_signature = urldecode($_GET['msg_signature']);
//    $timestamp = urldecode($_GET['timestamp']);
//    $nonce = urldecode($_GET['nonce']);
//
//    // post请求的密文数据
//    // $sReqData = HttpUtils.PostData();
//    //$sReqData = "<xml><ToUserName><![CDATA[wx5823bf96d3bd56c7]]></ToUserName><Encrypt><![CDATA[RypEvHKD8QQKFhvQ6QleEB4J58tiPdvo+rtK1I9qca6aM/wvqnLSV5zEPeusUiX5L5X/0lWfrf0QADHHhGd3QczcdCUpj911L3vg3W/sYYvuJTs3TUUkSUXxaccAS0qhxchrRYt66wiSpGLYL42aM6A8dTT+6k4aSknmPj48kzJs8qLjvd4Xgpue06DOdnLxAUHzM6+kDZ+HMZfJYuR+LtwGc2hgf5gsijff0ekUNXZiqATP7PF5mZxZ3Izoun1s4zG4LUMnvw2r+KqCKIw+3IQH03v+BCA9nMELNqbSf6tiWSrXJB3LAVGUcallcrw8V2t9EL4EhzJWrQUax5wLVMNS0+rUPA3k22Ncx4XXZS9o0MBH27Bo6BpNelZpS+/uh9KsNlY6bHCmJU9p8g7m3fVKn28H3KDYA5Pl/T8Z1ptDAVe0lXdQ2YoyyH2uyPIGHBZZIs2pDBS8R07+qN+E7Q==]]></Encrypt><AgentID><![CDATA[218]]></AgentID></xml>";
//    $sReqData = $_POST;
//    $sMsg = "";  // 解析之后的明文
//    $errCode = $this->wxcpt->DecryptMsg($msg_signature, $timestamp, $nonce, $sReqData, $sMsg);
//    if ($errCode == 0) {
//      // 解密成功，sMsg即为xml格式的明文
//      // TODO: 对明文的处理
//      // For example:
//      $xml = new DOMDocument();
//      $xml->loadXML($sMsg);
//      $content = $xml->getElementsByTagName('Content')->item(0)->nodeValue;
//      print("content: " . $content . "\n\n");
//      // ...
//      // ...
//    }
//    else {
//      print("ERR: " . $errCode . "\n\n");
//      //exit(-1);
//    }
//  }

  /*
  ------------使用示例三：企业回复用户消息的加密---------------
  企业被动回复用户的消息也需要进行加密，并且拼接成密文格式的xml串。
  假设企业需要回复用户的明文如下：
  <xml>
  <ToUserName><![CDATA[mycreate]]></ToUserName>
  <FromUserName><![CDATA[wx5823bf96d3bd56c7]]></FromUserName>
  <CreateTime>1348831860</CreateTime>
  <MsgType><![CDATA[text]]></MsgType>
  <Content><![CDATA[this is a test]]></Content>
  <MsgId>1234567890123456</MsgId>
  <AgentID>128</AgentID>
  </xml>

  为了将此段明文回复给用户，企业应：
  1.自己生成时间时间戳(timestamp),随机数字串(nonce)以便生成消息体签名，也可以直接用从公众平台的post url上解析出的对应值。
  2.将明文加密得到密文。
  3.用密文，步骤1生成的timestamp,nonce和企业在公众平台设定的token生成消息体签名。
  4.将密文，消息体签名，时间戳，随机数字串拼接成xml格式的字符串，发送给企业号。
  以上2，3，4步可以用公众平台提供的库函数EncryptMsg来实现。
  */
//  public function encodeMessage() {
//    // 需要发送的明文
//    $sRespData = "<xml><ToUserName><![CDATA[mycreate]]></ToUserName><FromUserName><![CDATA[wx5823bf96d3bd56c7]]></FromUserName><CreateTime>1348831860</CreateTime><MsgType><![CDATA[text]]></MsgType><Content><![CDATA[this is a test]]></Content><MsgId>1234567890123456</MsgId><AgentID>128</AgentID></xml>";
//    $sEncryptMsg = ""; //xml格式的密文
//    $errCode = $this->wxcpt->EncryptMsg($sRespData, $timestamp, $nonce, $sEncryptMsg);
//    if ($errCode == 0) {
//      // TODO:
//      // 加密成功，企业需要将加密之后的sEncryptMsg返回
//      // HttpUtils.SetResponce($sEncryptMsg);  //回复加密之后的密文
//    }
//    else {
//      print("ERR: " . $errCode . "\n\n");
//      // exit(-1);
//    }
//  }

}