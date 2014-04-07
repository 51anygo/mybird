/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.qgame.myflappybird;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.Stack;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import com.umeng.socialize.bean.SHARE_MEDIA;
import com.umeng.socialize.bean.SocializeEntity;
import com.umeng.socialize.controller.RequestType;
import com.umeng.socialize.controller.UMServiceFactory;
import com.umeng.socialize.controller.UMSocialService;
import com.umeng.socialize.controller.UMWXHandler;
import com.umeng.socialize.controller.listener.SocializeListeners;
import com.umeng.socialize.controller.listener.SocializeListeners.SnsPostListener;
import com.umeng.socialize.media.CircleShareContent;
import com.umeng.socialize.media.UMImage;
import com.umeng.socialize.sso.QZoneSsoHandler;
import com.umeng.socialize.sso.SinaSsoHandler;
import com.umeng.socialize.sso.TencentWBSsoHandler;
import com.umeng.update.UmengUpdateAgent;

import android.app.Activity;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.Looper;
import android.text.TextUtils;
import android.text.format.Time;
import android.widget.Toast;


import android.widget.TextView;
import android.view.Gravity;
import android.widget.FrameLayout;
import android.widget.RelativeLayout;

import com.baidu.mobads.IconsAd;


import com.baidu.mobads.AdSettings;
import com.baidu.mobads.AdView;
import com.baidu.mobads.AdViewListener;

import android.util.Log;

import org.json.JSONObject;



public class FlappyBird extends Cocos2dxActivity{
	 private static String mTmpPath = null;
	 public static Context STATIC_REF = null;
	 /**
     * Handler, 用于包装友盟的openShare方法，保证openShare方法在UI线程执行
     */
    private static Handler mHandler = null;
    /**
     * 保存当前Activity实例， 静态变量
     */
    private static Activity mActivity = null;
    /**
     * 友盟Social SDK实例，整个SDK的Controller
     */
    private static UMSocialService mController = UMServiceFactory.getUMSocialService(
                    "com.aigcar", RequestType.SOCIAL);

    /*** 
     * 删除文件或者文件夹 
     * @param f 
     * @return 成功 返回true, 失败返回false 
     */  
    static private boolean delFileUnRoot(File f) {  
        boolean ret = true;  
          
        if (null == f || false == f.exists()) {  
            return ret;  
        }  
          
        Stack<File> tmpFileStack = new Stack<File>();  
        tmpFileStack.push(f);  
          
        try {  
            while(false == tmpFileStack.isEmpty()) {  
                File curFile = tmpFileStack.pop();  
                if (null == curFile) {  
                    continue;  
                }  
                if (curFile.isFile()) {  
                    if (false == curFile.delete()) {  
                        ret = false;  
                    }  
                } else {  
                    File[] tmpSubFileList = curFile.listFiles();  
                    if (null == tmpSubFileList || 0 == tmpSubFileList.length) { //空文件夹直接删  
                        if (false == curFile.delete()) {  
                            ret = false;  
                        }  
                    } else {  
                        tmpFileStack.push(curFile); // !!!  
                        for (File item : tmpSubFileList) {  
                            tmpFileStack.push(item);  
                        }  
                    }  
                }  
            }  
        } catch (Exception e) {  
            ret = false;  
        }  
        return ret;  
    }  
    
    public static Context getContext(){
        return STATIC_REF;
    }
    


    
public static String getDeviceInfo(Context context) {
    try{
      org.json.JSONObject json = new org.json.JSONObject();
      android.telephony.TelephonyManager tm = (android.telephony.TelephonyManager) context
          .getSystemService(Context.TELEPHONY_SERVICE);
  
      String device_id = tm.getDeviceId();
      
      android.net.wifi.WifiManager wifi = (android.net.wifi.WifiManager) context.getSystemService(Context.WIFI_SERVICE);
          
      String mac = wifi.getConnectionInfo().getMacAddress();
      json.put("mac", mac);
      
      if( TextUtils.isEmpty(device_id) ){
        device_id = mac;
      }
      
      if( TextUtils.isEmpty(device_id) ){
        device_id = android.provider.Settings.Secure.getString(context.getContentResolver(),android.provider.Settings.Secure.ANDROID_ID);
      }
      
      json.put("device_id", device_id);
      
      return json.toString();
    }catch(Exception e){
      e.printStackTrace();
    }
  return null;
}
                  

    
    protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);	
		UmengUpdateAgent.setUpdateOnlyWifi(false);
		UmengUpdateAgent.update(this);
		String strdevinfo=getDeviceInfo(this);
		Log.w("", strdevinfo);
		///FeedbackAgent agent = new FeedbackAgent(this);
		STATIC_REF = this;
	    //agent.startFeedbackActivity();

		///agent.sync();
		mActivity = this;
		mTmpPath=Environment.getExternalStorageDirectory()+"/flappybirdtmp/";
		File f = new File(mTmpPath);
		    //先清理再创建
			if(f.exists()){
				      delFileUnRoot(f);
		              f.delete();
		     }
           if(!f.exists()){
                   f.mkdir();
           }
           if(true){
	           AdView adView = new AdView(this);
	   			// 设置监听器
	   			adView.setListener(new AdViewListener() {
	   			public void onAdSwitch() {
	   				Log.w("", "onAdSwitch");
	   			}
	   			public void onAdShow(JSONObject info) {
	   				Log.w("", "onAdShow " + info.toString());
	   			}
	   			public void onAdReady(AdView adView) {
	   				Log.w("", "onAdReady " + adView);
	   			}
	   			public void onAdFailed(String reason) {
	   				Log.w("", "onAdFailed " + reason);
	   			}
	   			public void onAdClick(JSONObject info) {
	   				Log.w("", "onAdClick " + info.toString());
	   			}
	   			public void onVideoStart() {
	   				Log.w("", "onVideoStart");
	   			}
	   			public void onVideoFinish() {
	   				Log.w("", "onVideoFinish");
	   			}
	   			@Override
	   			public void onVideoClickAd() {
	   				Log.w("", "onVideoFinish");
	   			}
	   			@Override
	   			public void onVideoClickClose() {
	   				Log.w("", "onVideoFinish");
	   			}
	   			@Override
	   			public void onVideoClickReplay() {
	   				Log.w("", "onVideoFinish");
	   			}
	   			@Override
	   			public void onVideoError() {
	   				Log.w("", "onVideoFinish");
	   			}
	   		});
	   		//rlMain.addView(adView);
	   		//setContentView(rlMain);
	   			
			FrameLayout.LayoutParams params = new FrameLayout.LayoutParams(  
	        FrameLayout.LayoutParams.WRAP_CONTENT,  
	        FrameLayout.LayoutParams.WRAP_CONTENT);
		
	        // 设置广告出现的位置(悬浮于顶部)  
	        params.topMargin = 0;  
	        params.gravity = Gravity.TOP | Gravity.CENTER_HORIZONTAL;
	   			       
	        RelativeLayout layout = new RelativeLayout(this); 
	        layout.addView(adView);
	        addContentView(layout, params); 
			
	        IconsAd iconsAd=new IconsAd(this,new int[]{R.drawable.mp_icon, R.drawable.mp_close });
			iconsAd.loadAd(this);   
           }
		/*
		RelativeLayout rlMain=new RelativeLayout(this);
		setContentView(iconsAd,params);
		IconsAd iconsAd=new IconsAd(this,new int[]{R.drawable.mp_icon, R.drawable.mp_close });
		iconsAd.loadAd(this);
		*/
		//shareTxtToTimeLine();
	}

    @Override
    protected void onDestroy() {
    super.onDestroy();
    //清空缓存目录
    File f = new File(mTmpPath);
            if(f.exists()){
                    f.delete();
            }
}
    /**
     * 载入cocos2d-x的c++代码,这里命名为umenggame
     */
    static {
    	System.loadLibrary("cocos2dcpp");
    }
    
    /*****************************************************************
     * ** 友盟分享回调
     *****************************************************************/
    public class UmengSnsPostListener implements SnsPostListener {
            @Override
            public void onStart() {
                    Toast.makeText(mActivity, "开始分享.", Toast.LENGTH_SHORT).show();
            }

         			@Override
			public void onComplete(SHARE_MEDIA arg0, int eCode,
					SocializeEntity arg2) {
				 if (eCode == 200) {
                     Toast.makeText(mActivity, "分享成功.", Toast.LENGTH_SHORT).show();
             } else {
                     String eMsg = "";
                     if (eCode == -101) {
                             eMsg = "没有授权";
                     }
                     Toast.makeText(mActivity, "分享失败[" + eCode + "] " + eMsg, Toast.LENGTH_SHORT).show();
             }
				
			}
    }
    
    public static native void nativeShareReturn(final int result);
    /**
     * @Title:  openShareBoard
     * @Description:
     *       调用友盟的openShare方法， 打开分享平台选择面板
     * @throws
     */
    public static void openShareBoard(final String strfile) {
        mHandler = new Handler(Looper.getMainLooper());
        mHandler.postDelayed(new Runnable() {
        	

            @Override
            public void run() {
                if (mActivity != null) {
                    /**
                     *   设置新浪微博、QQ空间、腾讯微博的Handler,进行SSO授权
                     *
                     *   注意 ： 新浪平台支持SSO则需要把友盟提供的com.sina.sso拷进src里面，
                     *      需要将友盟提供的libs、res文件拷贝到您的工程对应的目录里面.
                     */
                    //mController.getConfig().setSsoHandler(new SinaSsoHandler());
                    mController.getConfig().setSsoHandler(new QZoneSsoHandler(mActivity));
                    mController.getConfig().setSsoHandler(new TencentWBSsoHandler());
                    mController.getConfig().setPlatforms(SHARE_MEDIA.SINA,
                            SHARE_MEDIA.TENCENT, SHARE_MEDIA.WEIXIN,
                            SHARE_MEDIA.WEIXIN_CIRCLE, SHARE_MEDIA.QZONE,
                            SHARE_MEDIA.QQ,
                            SHARE_MEDIA.RENREN);

                    mController.getConfig().removePlatform(SHARE_MEDIA.SMS,SHARE_MEDIA.DOUBAN,
                           SHARE_MEDIA.EMAIL);
                    String strtitle="风靡全球的酷炫小鸟游戏";
                    //短网址 http://www.324324.cn/top/turl.html http://findme.jhost.cn/bird/index.html
                    String strurl="http://url.cn/KzKcUd";
                    String strcontent="我擦,小鸟又掉了,想砸手机,一起来玩吧! "+strurl;
                 // wx967daebe835fbeac是你在微信开发平台注册应用的AppID, 这里需要替换成你注册的AppID
                    String appID = "wx4f9303de03f14ad3";
                    // 微信图文分享必须设置一个url 
                    String contentUrl = strurl;
                    mController.getConfig().supportQQPlatform(mActivity, contentUrl);
                    // 添加微信平台，参数1为当前Activity, 参数2为用户申请的AppID, 参数3为点击分享内容跳转到的目标url
                    UMWXHandler wxHandler = mController.getConfig().supportWXPlatform(mActivity,appID, contentUrl);
                    //设置分享标题
                    wxHandler.setWXTitle(strtitle);
                    mController.setShareContent(strcontent);             //设置分享图片, 参数2为图片的地址
                    //            mController.setShareMedia(new UMImage(this, "http://www.umeng.com/images/pic/banner_module_social.png"));
                    //设置分享图片，参数2为本地图片的资源引用
                    String newpath=moveToTempPath(strfile);
                    mController.setShareMedia(new UMImage(mActivity, newpath));
                    //设置分享图片，参数2为本地图片的路径(绝对路径)
                    //mController.setShareMedia(new UMImage(getActivity(), 
                   //BitmapFactory.decodeFile("/mnt/sdcard/icon.png")));
                   try{
                    // 支持微信朋友圈
                    UMWXHandler circleHandler = mController.getConfig().supportWXCirclePlatform(mActivity,appID, contentUrl) ;
                    circleHandler.setCircleTitle(strcontent);             
                    CircleShareContent circleMedia = new CircleShareContent(new UMImage(mActivity,
                    		newpath));
                    circleMedia.setShareContent(strcontent);
                    mController.setShareMedia(circleMedia);                  

	                    SnsPostListener listener = new SnsPostListener(){
	                         @Override
	                         public void onStart() {
	                             Toast.makeText(mActivity, "分享开始",Toast.LENGTH_SHORT).show();
	                         }
	             
	                         @Override
	                         public void onComplete(SHARE_MEDIA platform,int eCode, SocializeEntity entity) {
	                             if(eCode == 200){
	                                 Toast.makeText(mActivity, "分享成功",Toast.LENGTH_SHORT).show();
	                                 nativeShareReturn(0);
	                             }else{
	                                 Toast.makeText(mActivity, "分享失败",Toast.LENGTH_SHORT).show();
	                                 nativeShareReturn(1);
	                             }
	                         }
	                    };
	                    mController.registerListener(listener);	              
	                    // 打开友盟的分享平台选择面板
	                    mController.openShare(mActivity, false);
                   }
                   catch(Exception ex){
                	   ex.printStackTrace();
                   }
                }
                }
        }, 100);
    }
    

    
    
    private void shareToFriend(File file) {
        Intent intent = new Intent();
        ComponentName comp = new ComponentName("com.tencent.mm",
                        "com.tencent.mm.ui.tools.ShareImgUI");
        intent.setComponent(comp);
        intent.setAction("android.intent.action.SEND");
        intent.setType("image/*");                 
        intent.putExtra(Intent.EXTRA_TEXT,"我是文字");
        intent.putExtra(Intent.EXTRA_STREAM, Uri.fromFile(file));               
        startActivity(intent);
    }
    
    public static  String moveToTempPath(final String strfile) {
    	String newpath="";
    	File file =new File(strfile);
        if(file.exists()){
        	 Time time = new Time("GMT+8");    
			 time.setToNow();   
			 int year = time.year;   
			 int month = time.month;   
			 int day = time.monthDay;   
			 int minute = time.minute;   
			 int hour = time.hour;   
			 int sec = time.second;  
		     String strfilename=""+year+month+day+minute+hour+sec+".png";
        	 newpath=mTmpPath+strfilename;//"sc.png";
        	 File newfile = new File(newpath);  
        	 InputStream in = null;
        	 FileOutputStream out = null;
        	 try {
	        	 in = new FileInputStream(file);
				 out = new FileOutputStream(newfile);
				 byte[] buffer = new byte[1024];
				    int read;
				    while((read = in.read(buffer)) != -1){
				      out.write(buffer, 0, read);
				    }
			} catch (FileNotFoundException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} 
        	finally{
        	   	try {
        	   		if(out!=null){
        	   			out.close();
        	   		}
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
        	   	
        	}
        }
        File newfile =new File(newpath);
        if(newfile.exists()){
        	return newpath;
        }
        return "";
    }
 
    public static  void shareTxtToTimeLine(final String strfile) {
	  mHandler = new Handler(Looper.getMainLooper());
      mHandler.postDelayed(new Runnable() {
          @Override
          public void run() {
		        Intent intent = new Intent();
		        ComponentName comp = new ComponentName("com.tencent.mm",
		                        "com.tencent.mm.ui.tools.ShareToTimeLineUI");
		        intent.setComponent(comp);
		        intent.setAction("android.intent.action.SEND");
		        intent.setType("image/*");
		        //File file =new File("/sdcard/download/ScreenShoot.png");
		       	
			        //intent.putExtra(Intent.EXTRA_TEXT,"13123123");
		        	 String newpath=moveToTempPath(strfile);
		        	 File newnewfile =new File(newpath); 
		        	 intent.putExtra(Intent.EXTRA_TEXT,"我是文字");
			         intent.putExtra(Intent.EXTRA_STREAM, Uri.fromFile(newnewfile));

		        
		        mActivity.startActivity(intent);
              }
      }, 100);
  } 
	private void shareToTimeLine(File file) {
	        Intent intent = new Intent();
	        ComponentName comp = new ComponentName("com.tencent.mm",
	                        "com.tencent.mm.ui.tools.ShareToTimeLineUI");
	        intent.setComponent(comp);
	        intent.setAction("android.intent.action.SEND");
	        intent.setType("image/*");
	        intent.putExtra(Intent.EXTRA_TEXT,"我是文字");
	        intent.putExtra(Intent.EXTRA_STREAM, Uri.fromFile(file));
	        startActivity(intent);
	}
	
	private void shareMultiplePictureToTimeLine(File... files) {
        Intent intent = new Intent();
        ComponentName comp = new ComponentName("com.tencent.mm",
                        "com.tencent.mm.ui.tools.ShareToTimeLineUI");
        intent.setComponent(comp);
        intent.setAction(Intent.ACTION_SEND_MULTIPLE);
        intent.setType("image/*");
         
        ArrayList<Uri> imageUris = new ArrayList<Uri>();
        for (File f : files) {
                imageUris.add(Uri.fromFile(f));
        }
        intent.putParcelableArrayListExtra(Intent.EXTRA_STREAM, imageUris);
         
        startActivity(intent);
}

    
    public static void Feedback() {
    	//FeedbackAgent agent = new FeedbackAgent(mActivity);
	    // agent.startFeedbackActivity();
    	 }
    public Cocos2dxGLSurfaceView onCreateView() {
    	Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
    	// FlappyBird should create stencil buffer
    	glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
    	
    	return glSurfaceView;
    }

    static {
        System.loadLibrary("cocos2dcpp");
    }     
}
