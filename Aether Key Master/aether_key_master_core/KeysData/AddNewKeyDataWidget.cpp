#include "AddNewKeyDataWidget.h"
#include "Utility/Utility.h"
#include "MainWindow.h"

#include "Aether CPP Logger/include/Logger.h"

namespace aether_key_master_core
{
	AddNewKeyDataWidget::AddNewKeyDataWidget(QPointer<User> user, QWidget* parent)
		: FadeInAnimation(parent), m_user(user)
	{
		ui.setupUi(this);

		initializeUI();
		initializeConnections();
	}

	void AddNewKeyDataWidget::initializeUI()
	{
		//Set the properties of the widget
		setWindowModality(Qt::WindowModality::ApplicationModal);
		setWindowFlags(Qt::FramelessWindowHint);
		setAttribute(Qt::WA_DeleteOnClose);
		setAutoFillBackground(true);

		//Change the size policy of the information label and hide it
		auto errorInformationLabelSizePolicy = ui.m_errorInformation_lbl->sizePolicy();
		errorInformationLabelSizePolicy.setRetainSizeWhenHidden(true);
		ui.m_errorInformation_lbl->setSizePolicy(errorInformationLabelSizePolicy);
		ui.m_errorInformation_lbl->setVisible(false);
	}

	void AddNewKeyDataWidget::initializeConnections() const
	{
		connect(ui.m_cancel_btn, &QPushButton::clicked, this, &AddNewKeyDataWidget::slot_canceled);
		connect(ui.m_add_btn, &QPushButton::clicked, this, &AddNewKeyDataWidget::slot_add);
	}

	QString AddNewKeyDataWidget::checkTitleDuplication(const QString& baseTitle, int index)
	{
		QString title = baseTitle;
		//If the index is greater than 1 the base title is duplicated
		//Add the duplication count to the base title so a new unique title is created
		if (index > 1)
		{
			title += QString(" %0").arg(index);
		}

		//Check the stored KeyData QVector for title duplication
		const auto& storedKeys = m_user->storedKeys();
		for (const auto& keyData : storedKeys)
		{
			//If there is a duplication increase counter
			//and run the title check anew
			if (keyData.title() == title)
			{
				++index;
				return checkTitleDuplication(baseTitle, index);
			}
		}

		return title;
	}

	void AddNewKeyDataWidget::slot_add()
	{
		//Get the base title from the UI and check it for duplication
		const auto title = checkTitleDuplication(ui.m_title_lineEdit->text());
		//If the title is empty show error message and do not save the new KeyData
		if (title.trimmed().isEmpty())
		{
			AETHER_LOG_ERROR("New KeyData error: Title is empty");

			changeWidgetSeverityStyle(ui.m_title_lineEdit, "error");
			ui.m_errorInformation_lbl->setVisible(true);
			return;
		}

		const auto username = ui.m_username_lineEdit->text();
		const auto password = ui.m_password_lineEdit->text();

		//Create a new KeyData and store it in the user
		const KeyData newKeyData(title, username, password);
		m_user->addKeyData(newKeyData);
		m_user->saveKeys();

		MainWindow::showNotification(QString("Key data added - %0").arg(title));

		close();
	}

	void AddNewKeyDataWidget::slot_canceled()
	{
		close();
	}
}