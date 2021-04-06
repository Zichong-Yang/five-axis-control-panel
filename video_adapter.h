#ifndef VIDEOADAPTER_H
#define VIDEOADAPTER_H

#include <QWidget>
#include <QTimer>
#include <QCamera>
#include <QKeyEvent>
#include <QCameraImageCapture>
#include <QMediaRecorder>
#include <QScopedPointer>

QT_BEGIN_NAMESPACE
namespace Ui { class VideoAdapter; }
QT_END_NAMESPACE

class VideoAdapter : public QWidget
{
    Q_OBJECT

public:
    VideoAdapter(QWidget *parent = nullptr);
    ~VideoAdapter();

private slots:
    void setCamera(const QCameraInfo &cameraInfo);

    void startCamera(); //打开相机，切换stackWidget
    void stopCamera(); //如果打开，关闭相机，切换stackWidget

    void toggleLock();
    void takeImage();
    void displayCaptureError(int, QCameraImageCapture::Error, const QString &errorString);

    void configureCaptureSettings();
    void configureVideoSettings();
    void configureImageSettings();

    void displayRecorderError();
    void displayCameraError();

    //void updateCameraDevice(QString device);

    void updateCameraState(QCamera::State);
    void updateCaptureMode();
    void setExposureCompensation(int index);

    void processCapturedImage(int requestId, const QImage &img);
    void updateLockStatus(QCamera::LockStatus, QCamera::LockChangeReason);

    void displayViewfinder();
    void displayCapturedImage();

    void readyForCapture(bool ready);
    void imageSaved(int id, const QString &fileName);

    void cameraStatusChanged(bool camera_permission, QString desired_camera_description); //接受相机名称

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::VideoAdapter *ui;

    QScopedPointer<QCamera> m_camera;
    bool is_camera_open_ = false; //接受主窗口信息，在statusChanged中修改

    QScopedPointer<QCameraImageCapture> m_imageCapture;
    QScopedPointer<QMediaRecorder> m_mediaRecorder;

    QImageEncoderSettings m_imageSettings;
    QAudioEncoderSettings m_audioSettings;
    QVideoEncoderSettings m_videoSettings;
    QString m_videoContainerFormat;
    bool m_isCapturingImage = false;
    bool m_applicationExiting = false;
};
#endif // VIDEOADAPTER_H
