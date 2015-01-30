all:sdk.docx sdk.html
.PHONY:clean

sdk.docx:sdk.markdown
	pandoc -s -o$@ $^

sdk.html:sdk.markdown
	pandoc -s -c github.css -o$@ $^

upload:sdk.html
	(cd `git rev-parse --show-toplevel`; git archive --format=tar --prefix s3-sdk-samples/ HEAD) | gzip > s3-sdk-samples.tar.gz
	s3cmd put -P s3-sdk-samples.tar.gz s3://test
	s3cmd put -P sdk.html s3://test
	s3cmd put --mime-type text/css -P github.css s3://test
	s3cmd put -P sdk-img/* s3://test/sdk-img/

clean:
	rm -f sdk.docx
	rm -f sdk.html
	rm -f s3-sdk-samples.tar.gz
