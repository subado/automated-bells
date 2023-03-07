import { addListeners } from "/utils.js";
import * as Data from "/data.js";

async function drawList() {
	const tables = await Data.get("/tables");
	const list = document.querySelector("#list");

	tables.forEach(element => {
		list.innerHTML += `
			<li>
				<input type="button" class="link" value="${element}">
				<input type="radio" name="table" value="${element}">
			</li>`
	});
	addListeners("input.link", "click", (event) => {
		const button = event.target;
		localStorage.setItem("table", button.value);
		window.location.href = "/table";
	});
	addListeners("input[name=table][type=radio]", "change", (event) => {
		const radio = event.target;
		Data.send("/shedule", JSON.stringify(radio.value));
	});
}

async function checkShedule() {
	const shedule = await Data.get("/shedule");
	if (shedule != "")
	{
		document.querySelector(`input[type=radio][value=${shedule}]`).checked = true;
	}
}

async function updateTime() {
	const time = await Data.get("/time");
	document.querySelector("#time").innerHTML = time;
}

drawList();
checkShedule();
updateTime();
setInterval(updateTime, 1000);
