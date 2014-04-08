package com.qgame.myflappybird.wxapi;

import android.os.Bundle;
import android.widget.Toast;

import com.tencent.mm.sdk.openapi.BaseReq;
import com.tencent.mm.sdk.openapi.BaseResp;
import com.umeng.socialize.view.WXCallbackActivity;

public class WXEntryActivity extends WXCallbackActivity {

	@Override
	public void onResp(BaseResp arg0) {
		// TODO Auto-generated method stub
		super.onResp(arg0);
		Toast.makeText(this,arg0.errCode+arg0.errStr,Toast.LENGTH_SHORT).show();
	}

	@Override
	protected void onCreate(Bundle arg0) {
		// TODO Auto-generated method stub
		super.onCreate(arg0);
	}

	@Override
	public void onReq(BaseReq arg0) {
		// TODO Auto-generated method stub
		super.onReq(arg0);
		Toast.makeText(this,arg0.toString()+arg0.toString(),Toast.LENGTH_SHORT).show();
	}

}