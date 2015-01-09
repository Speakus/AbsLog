Pod::Spec.new do |s|
  s.name         = 'AbsLog'
  s.version      = '1.0.9174'
  s.summary      = 'Logging framework'
  s.description  = <<-DESC
                   look AbsLog.h + AbsLogRequiredExternalSymbols.h
                   for API detail
                   DESC
  s.license      = 'MIT'
  s.author       = { 'Maxim Nikolaevich' => 'www.speakus.net' }
  s.platform     = :ios, '3.1'
  s.frameworks   = 'UIKit', 'Foundation'
  s.ios.vendored_frameworks = 'AbsLog.framework'
end
