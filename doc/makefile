all:sdk.docx sdk.html
.PHONY:clean

sdk.docx:sdk.markdown
	pandoc -o$@ $^

sdk.html:sdk.markdown
	pandoc -o$@ $^

clean:
	rm -f sdk.docx
	rm -f sdk.html
