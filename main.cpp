#include <QCommandLineParser>
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QImage>
#include <iostream>

QString CreateSaveToFilePath(const QString& sourceFilePath, const QString& ext)
{
	QFileInfo fi(sourceFilePath);
	const QString baseName = fi.baseName();
	const QString folder = fi.dir().absolutePath();
	return QDir::cleanPath(folder + QDir::separator() + baseName + "." + ext);
}

int main(int argc, char* argv[])
{
	QCoreApplication app(argc, argv);
	QCoreApplication::setApplicationName("imgtowebp");
	QCoreApplication::setApplicationVersion("1.0");

	QCommandLineParser parser;
	parser.setApplicationDescription("Convert image to WebP");
	parser.addHelpOption();
	parser.addVersionOption();

	parser.addPositionalArgument("source", "Source file to convert");

	parser.process(app);

	const QStringList args = parser.positionalArguments();

	if (args.count() < 1) {
		std::wcout << "Arguments missing. Use -h for help" << std::endl;
		return -1;
	}

	const QString sourceFilePath = args.at(0);
	if (sourceFilePath.isEmpty()) {
		std::wcout << L"Source file path missing" << std::endl;
		return -1;
	}

	QImage image;
	if (!image.load(sourceFilePath)) {
		std::wcout << L"Failed to load file:" << sourceFilePath.toStdWString();
		return -1;
	}

	const QString saveToFilePath = CreateSaveToFilePath(sourceFilePath, "webp");
	if (!image.save(saveToFilePath)) {
		std::wcout << L"Failed to save file:" << saveToFilePath.toStdWString();
		return -1;
	}

	std::wcout << L"[OK] Convert" << sourceFilePath.toStdWString() << L" to:"
			   << saveToFilePath.toStdWString() << std::endl;
	return 0;
}