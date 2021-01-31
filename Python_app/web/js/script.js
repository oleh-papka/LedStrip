async function get_ports(){
	let port = await eel.ports_availabe()();
	if(port == 1){
		alert("Error: no devices found");
	}
	else{
		document.getElementById('ports').value = port;
	}
}


async function set_new_port(){
	var port = document.getElementById('port_set').value;
	if (document.getElementById("port_set").value.length != 0){
		let message = await eel.set_port(port)();
		if(message == 1){
			alert("Error: wrong port")
		}
	}
}

async function save_for_app(){
	eel.save_for_app();
	document.getElementById('save-for-app').value = "All settings been saved for app";
}

async function restore_for_app(){
	eel.restore_for_app();
	document.getElementById('restore-for-app').value = "All settings been reset for app";
}

async function save_for_arduino(){
	eel.save_for_arduino();
	document.getElementById('save-for-all').value = "All settings been saved for Arduino & app";
}

async function restore_for_arduino(){
	eel.restore_for_arduino();
	document.getElementById('restore-for-all').value = "All settings been reset for Arduino & app";
}


async function get_set_color(){
	var color = document.getElementById("color_picker").value;
	eel.get_set_color(color);
}

async function get_set_preset_color1(){
	var color = document.getElementById("color_picker_pr1").value;
	eel.get_set_preset_color1(color);
}

async function get_set_preset_color2(){
	var color = document.getElementById("color_picker_pr2").value;
	eel.get_set_preset_color2(color);
}

async function get_set_preset_color3(){
	var color = document.getElementById("color_picker_pr3").value;
	eel.get_set_preset_color3(color);
}

async function set_preset_color1(){
	eel.set_preset_color1();
}

async function set_preset_color2(){
	eel.set_preset_color2();
}

async function set_preset_color3(){
	eel.set_preset_color3();
}

async function get_rainbow(){
	var speed = document.getElementById("speed").value;
	if (document.getElementById("speed").value.length == 0){
		speed = 20;
		document.getElementById("speed").value = 20;
	}
	if (speed < 20) {
		speed = 20;
		document.getElementById("speed").value = 20;
	}
	if (speed > 255) {
		speed = 255;
		document.getElementById("speed").value = 255;
	}
	
	var size = document.getElementById("size").value;
	if (document.getElementById("size").value.length == 0) {
		size = 7;
		document.getElementById("size").value = 7;
	}
	if (size < 1) {
		size = 1;
		document.getElementById("size").value = 1;
	}
	if (size > 20) {
		size = 20;
		document.getElementById("size").value = 20;
	}
	
	eel.get_rainbow(speed, size);
}


async function get_rainbow_preset1(){
	var speed = document.getElementById("speed_pr1").value;
	if (document.getElementById("speed_pr1").value.length == 0){
		speed = 20;
		document.getElementById("speed_pr1").value = 20;
	}
	if (speed < 20) {
		speed = 20;
		document.getElementById("speed_pr1").value = 20;
	}
	if (speed > 255) {
		speed = 255;
		document.getElementById("speed_pr1").value = 255;
	}
	
	var size = document.getElementById("size_pr1").value;
	if (document.getElementById("size_pr1").value.length == 0) {
		size = 7;
		document.getElementById("size_pr1").value = 7;
	}
	if (size < 1) {
		size = 1;
		document.getElementById("size_pr1").value = 1;
	}
	if (size > 20) {
		size = 20;
		document.getElementById("size_pr1").value = 20;
	}
	
	eel.get_rainbow_preset1(speed, size);
}

async function get_rainbow_preset2(){
	var speed = document.getElementById("speed_pr2").value;
	if (document.getElementById("speed_pr2").value.length == 0){
		speed = 20;
		document.getElementById("speed_pr2").value = 20;
	}
	if (speed < 20) {
		speed = 20;
		document.getElementById("speed_pr2").value = 20;
	}
	if (speed > 255) {
		speed = 255;
		document.getElementById("speed_pr2").value = 255;
	}
	
	var size = document.getElementById("size_pr2").value;
	if (document.getElementById("size_pr2").value.length == 0) {
		size = 7;
		document.getElementById("size_pr2").value = 7;
	}
	if (size < 1) {
		size = 1;
		document.getElementById("size_pr2").value = 1;
	}
	if (size > 20) {
		size = 20;
		document.getElementById("size_pr2").value = 20;
	}
	
	eel.get_rainbow_preset2(speed, size);
}


async function set_preset_rainbow1(){
	eel.set_preset_rainbow1();
}

async function set_preset_rainbow2(){
	eel.set_preset_rainbow2();
}




async function get_gradient(){
	var color1 = document.getElementById("color_picker1").value;
	var color2 = document.getElementById("color_picker2").value;
	eel.get_gradient(color1, color2);
}

async function get_gradient_preset1(){
	var color1 = document.getElementById("color_picker1_pr1").value;
	var color2 = document.getElementById("color_picker2_pr1").value;
	eel.get_gradient_preset1(color1, color2);
}

async function get_gradient_preset2(){
	var color1 = document.getElementById("color_picker1_pr2").value;
	var color2 = document.getElementById("color_picker2_pr2").value;
	eel.get_gradient_preset2(color1, color2);
}

async function set_preset_gradient1(){
	eel.set_preset_gradient1();
}

async function set_preset_gradient2(){
	eel.set_preset_gradient2();
}



async function get_strobe(){
	var color = document.getElementById("color_picker").value;
	var speed = document.getElementById("speed").value;
	if (document.getElementById("speed").value.length == 0) {
		speed = 100;
		document.getElementById("speed").value = 100;
	}
	if (speed < 30) {
		speed = 30;
		document.getElementById("speed").value = 30;
	}
	if (speed > 255) {
		speed = 255;
		document.getElementById("speed").value = 255;
	}
	eel.get_strobe(color, speed);
}

async function get_matrix(){
	var color = document.getElementById("color_picker").value;
	var speed = document.getElementById("speed").value;
	if (document.getElementById("speed").value.length == 0) {
		speed = 100;
		document.getElementById("speed").value = 100;
	}
	if (speed < 30) {
		speed = 30
		document.getElementById("speed").value = 30;
	}
	if (speed > 255) {
		speed = 255;
		document.getElementById("speed").value = 255;
	}
	eel.get_matrix(color, speed);
}

async function get_brightness(){
	var val = document.getElementById("slider").value
	eel.get_brightness(val);
}

async function get_police_siren(){
	if (document.getElementById("blue").checked){
		var type = 0;
	}
	else{
		var type = 1;
	}
		
	var speed = document.getElementById("speed").value
	if (document.getElementById("speed").value.length == 0) {
		speed = 100;
		document.getElementById("speed").value = 100;
	}
	if (speed < 30) {
		speed = 30;
		document.getElementById("speed").value = 30;
	}
	if (speed > 255) {
		speed = 255;
		document.getElementById("speed").value = 255;
	}
	eel.get_police_siren(speed, type);
}