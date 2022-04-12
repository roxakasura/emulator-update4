USE [MuOnline]
GO

/****** Object:  Table [dbo].[EventGoldenArcher]    Script Date: 03/30/2022 12:14:43 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

SET ANSI_PADDING ON
GO

CREATE TABLE [dbo].[EventGoldenArcher](
	[Account] [varchar](10) NOT NULL,
	[RenaCount] [int] NOT NULL
) ON [PRIMARY]

GO

SET ANSI_PADDING OFF
GO

ALTER TABLE [dbo].[EventGoldenArcher] ADD  CONSTRAINT [DF_EventGoldenArcherCount_RenaCount]  DEFAULT ((0)) FOR [RenaCount]
GO


