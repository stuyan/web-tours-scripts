Action()
{
	lr_start_transaction("UC_6_Login_Logout");
	
		lr_start_transaction("connect");
	
			web_add_auto_header("DNT", 
				"1");
		
			web_add_auto_header("Upgrade-Insecure-Requests", 
				"1");
		
			web_reg_find("Fail=NotFound",
				"Text=The document has moved",
				LAST);
		
		/*Correlation comment: Automatic rules - Do not change!  
		Original value='129609.170595383zzzzHHVpHVcftAAAApzDAcHf' 
		Name ='userSession' 
		Type ='Rule' 
		AppName ='WebTours' 
		RuleName ='UserSession'*/
			web_reg_save_param_attrib(
				"ParamName=userSession",
				"TagName=input",
				"Extract=value",
				"Name=userSession",
				"Type=hidden",
				SEARCH_FILTERS,
				"RequestUrl=*/nav.pl*",
				LAST);
		
			web_url("WebTours", 
				"URL=http://localhost:1080/WebTours", 
				"TargetFrame=", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=", 
				"Snapshot=t1.inf", 
				"Mode=HTML", 
				LAST);
		
			web_set_sockets_option("SSL_VERSION", "AUTO");
		
			web_websocket_send("ID=0", 
				"Buffer={\"messageType\":\"hello\",\"broadcasts\":{\"remote-settings/monitor_changes\":\"\\\"1599847578511\\\"\"},\"use_webpush\":true,\"uaid\":\"ddaed336ef8242e789f503edeab84ad5\"}", 
				"IsBinary=0", 
				LAST);
		
		lr_end_transaction("connect", LR_AUTO);
	
		/*Connection ID 0 received buffer WebSocketReceive0*/
	
		lr_start_transaction("login");
	
			web_revert_auto_header("Upgrade-Insecure-Requests");
		
			web_add_header("Origin", 
				"http://localhost:1080");
		
			lr_think_time(24);
			
			web_reg_find("Fail=NotFound",
				"Text=User password was correct",
				LAST);
		
			web_submit_data("login.pl",
				"Action=http://localhost:1080/cgi-bin/login.pl",
				"Method=POST",
				"TargetFrame=body",
				"RecContentType=text/html",
				"Referer=http://localhost:1080/cgi-bin/nav.pl?in=home",
				"Snapshot=t2.inf",
				"Mode=HTML",
				ITEMDATA,
				"Name=userSession", "Value={userSession}", ENDITEM,
				"Name=username", "Value={login}", ENDITEM,
				"Name=password", "Value={password}", ENDITEM,
				"Name=login.x", "Value=29", ENDITEM,
				"Name=login.y", "Value=13", ENDITEM,
				"Name=JSFormSubmit", "Value=off", ENDITEM,
				LAST);
	
		lr_end_transaction("login",LR_AUTO);
	
		lr_start_transaction("logout");
	
			web_add_header("Upgrade-Insecure-Requests", 
				"1");
		
			lr_think_time(16);
			
			web_reg_find("Fail=NotFound",
			"Text=Username",
			LAST);

			web_url("welcome.pl", 
				"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
				"TargetFrame=", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=flights", 
				"Snapshot=t7.inf", 
				"Mode=HTML", 
				LAST);
	
		lr_end_transaction("logout",LR_AUTO);

	lr_end_transaction("UC_6_Login_Logout",LR_AUTO);

	return 0;
}