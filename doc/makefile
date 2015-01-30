all:sdk.docx sdk.html
.PHONY:clean

sdk.docx:sdk.markdown
	pandoc -s -o$@ $^

sdk.html:sdk.markdown
	pandoc -s -t html5 -c github.css -o$@ $^

clean:
	rm -f sdk.docx
	rm -f sdk.html
