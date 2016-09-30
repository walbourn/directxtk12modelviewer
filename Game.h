//
// Game.h
//

#pragma once

#include "StepTimer.h"
#include "ArcBall.h"

#if defined(_XBOX_ONE) && defined(_TITLE)
#include "DeviceResourcesXDK.h"
#else
#include "DeviceResourcesPC.h"
#endif


// A basic game implementation that creates a D3D12 device and
// provides a game loop.
class Game
#if !defined(_XBOX_ONE) || !defined(_TITLE)
    : public DX::IDeviceNotify
#endif
{
public:

    Game();
    ~Game();

    // Initialization and management
#if defined(_XBOX_ONE) && defined(_TITLE)
    void Initialize(IUnknown* window);
#else
    void Initialize(HWND window, int width, int height);
#endif

    // Basic game loop
    void Tick();

#if !defined(_XBOX_ONE) || !defined(_TITLE)
    // IDeviceNotify
    virtual void OnDeviceLost() override;
    virtual void OnDeviceRestored() override;
#endif

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height);
    void OnFileOpen(const WCHAR* filename);

    // Properties
    void GetDefaultSize( int& width, int& height ) const;

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

    void LoadModel();
    void DrawGrid(ID3D12GraphicsCommandList *commandList);
    void DrawCross(ID3D12GraphicsCommandList *commandList);

    void CameraHome();

    void CycleBackgroundColor();

    void CreateProjection();

    void RotateView(DirectX::SimpleMath::Quaternion& q);

#if defined(_XBOX_ONE) && defined(_TITLE)
    void EnumerateModelFiles();
#endif

    // Device resources.
    std::unique_ptr<DX::DeviceResources>            m_deviceResources;

    // Rendering loop timer.
    DX::StepTimer                                   m_timer;

    std::unique_ptr<DirectX::GraphicsMemory>        m_graphicsMemory;
    std::unique_ptr<DirectX::DescriptorHeap>        m_resourceDescriptors;
    std::unique_ptr<DirectX::CommonStates>          m_states;

    std::unique_ptr<DirectX::BasicEffect>                                   m_lineEffect;
    std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>  m_lineBatch;

    std::unique_ptr<DirectX::EffectFactory>         m_fxFactory;
    std::unique_ptr<DirectX::EffectTextureFactory>  m_modelResources;
    std::unique_ptr<DirectX::Model>                 m_model;
    std::vector<std::shared_ptr<DirectX::IEffect>>  m_modelClockwise;
    std::vector<std::shared_ptr<DirectX::IEffect>>  m_modelCounterClockwise;
    std::vector<std::shared_ptr<DirectX::IEffect>>  m_modelWireframe;

    std::unique_ptr<DirectX::SpriteBatch>           m_spriteBatch;
    std::unique_ptr<DirectX::SpriteFont>            m_fontConsolas;
    std::unique_ptr<DirectX::SpriteFont>            m_fontComic;

    enum Descriptors
    {
        ConsolasFont,
        ComicFont,
        Count
    };

    std::unique_ptr<DirectX::GamePad>               m_gamepad;
    std::unique_ptr<DirectX::Keyboard>              m_keyboard;
    std::unique_ptr<DirectX::Mouse>                 m_mouse;

    DirectX::Keyboard::KeyboardStateTracker         m_keyboardTracker;
    DirectX::Mouse::ButtonStateTracker              m_mouseButtonTracker;
    DirectX::GamePad::ButtonStateTracker            m_gamepadButtonTracker;

    DirectX::SimpleMath::Matrix                     m_world;
    DirectX::SimpleMath::Matrix                     m_view;
    DirectX::SimpleMath::Matrix                     m_proj;

    DirectX::SimpleMath::Vector3                    m_cameraFocus;
    DirectX::SimpleMath::Vector3                    m_lastCameraPos;
    DirectX::SimpleMath::Quaternion                 m_cameraRot;
    DirectX::SimpleMath::Quaternion                 m_viewRot;
    DirectX::SimpleMath::Color                      m_clearColor;
    DirectX::SimpleMath::Color                      m_uiColor;

    DirectX::SimpleMath::Quaternion                 m_modelRot;

    float                                           m_gridScale;
    float                                           m_fov;
    float                                           m_zoom;
    float                                           m_distance;
    float                                           m_farPlane;
    float                                           m_sensitivity;
    size_t                                          m_gridDivs;

    bool                                            m_showHud;
    bool                                            m_showCross;
    bool                                            m_showGrid;
    bool                                            m_usingGamepad;
    bool                                            m_wireframe;
    bool                                            m_ccw;
    bool                                            m_reloadModel;
    bool                                            m_lhcoords;
    bool                                            m_fpscamera;

    WCHAR                                           m_szModelName[MAX_PATH];
    WCHAR                                           m_szStatus[512];
    WCHAR                                           m_szError[512];

    ArcBall                                         m_ballCamera;
    ArcBall                                         m_ballModel;

    int                                             m_selectFile;
    int                                             m_firstFile;
    std::vector<std::wstring>                       m_fileNames;
};