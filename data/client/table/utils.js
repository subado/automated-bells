function getRowOfButton(button)
{
	return getParentElement(button, "tr");
}

function getParentElement(element, parent)
{
	while (element.localName != parent)
	{
		element = element.parentElement;
	}

	return element;
}

function loadArray(array, dynamicTable)
{
	deleteChildren(dynamicTable.table.tBodies[0]);

	for (let i = 0; i < array.length; i++)
	{
		dynamicTable.addRow();
		dynamicTable.table.tBodies[0].rows[i].querySelector('input[name="time"]').value = array[i];
	}
}

function deleteChildren(element)
{
	let first = element.firstElementChild;

	while (first)
	{
		first.remove();
		first = element.firstElementChild;
	}
}
