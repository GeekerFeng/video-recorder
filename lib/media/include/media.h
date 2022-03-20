#pragma once

class Media
{
	private:
		string sDevPath;
	public:
		Media() { sDevPath = ""; }
		Media(string sPath): sDevPath(sPath) {}

		void setDevPath(string sPath);
		string getDevPath();
		void showDevPath();

		void open(void);
		void close(void);
		void readFrame(void);
		void setFrameRate(void);
		void setFrameResolution(void);
}
