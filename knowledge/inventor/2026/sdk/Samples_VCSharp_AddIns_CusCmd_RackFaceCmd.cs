using System;
using System.Runtime.InteropServices;
using Inventor;

namespace CustomCommand
{
	internal class RackFaceCmd : CustomCommand.Command
	{
		//rack face command dialog
		private RackFaceCmdDlg m_rackFaceCmdDlg;

		//rack face command parameters
		private Face m_rackFace;
		private Edge m_rackEdge;

		private int m_noTeeth;
		private double m_rackHeight;
		private double m_rackWidth;
		private double m_rackExtents;
		private PartFeatureExtentDirectionEnum m_rackFeatureExtentDirection;
	
		//rack face preview objects
		private GraphicsNode m_previewClientGraphicsNode;
		private TriangleStripGraphics m_triangleStripGraphics;
		private GraphicsCoordinateSet m_graphicsCoordinateSet;
		private GraphicsColorSet m_graphicsColorSet;
		private GraphicsIndexSet m_graphicsColorIndexSet;
	
		public RackFaceCmd()
		{
			m_rackFaceCmdDlg = null;

			m_rackFace = null;
			m_rackEdge = null;

			m_previewClientGraphicsNode = null;
			m_triangleStripGraphics = null;
			m_graphicsCoordinateSet = null;
			m_graphicsColorSet = null;
			m_graphicsColorIndexSet = null;
		}

		protected override void ButtonDefinition_OnExecute (NameValueMap context)
		{	
			//make sure that the current environment is "Part Environment"
			Inventor.Environment currEnvironment = m_application.UserInterfaceManager.ActiveEnvironment;
			if (currEnvironment.InternalName != "PMxPartEnvironment")
			{
				System.Windows.Forms.MessageBox.Show("This command applies only to Part Environment");
				return;
			}

			//if command was already started, stop it first
			if (m_commandIsRunning)
			{
				StopCommand();
			}

			//start new command
			StartCommand();
		}

		public override void StartCommand()
		{	
			//call base command button's StartCommand (to also start interaction)
			base.StartCommand();

			//implement this command specific functionality
			//subscribe to desired interaction event(s)
			base.SubscribeToEvent(Interaction.InteractionTypeEnum.kSelection);

			//initialize interaction graphics objects
			InitializePreviewGraphics();

			//create and display the dialog
			m_rackFaceCmdDlg = new RackFaceCmdDlg(m_application, this);

			if (m_rackFaceCmdDlg != null)
			{
				m_rackFaceCmdDlg.Activate();
				m_rackFaceCmdDlg.TopMost = true;
				m_rackFaceCmdDlg.ShowInTaskbar = false;
				m_rackFaceCmdDlg.Show();
			}

			//initialize this command's data members
			m_rackFace = null;
			m_rackEdge = null;

			//enable interaction
			EnableInteraction();
		}

		public override void ExecuteCommand()
		{	
			//stop the command (to disconnect interaction events, interaction graphics and dismiss command dialog)
			StopCommand();

			//create the rack face request
			RackFaceRequest rackFaceRequest = new RackFaceRequest(m_application, m_rackFace, m_rackEdge, m_noTeeth, m_rackHeight, m_rackWidth, m_rackExtents, m_rackFeatureExtentDirection);

			//execute the request
            base.ExecuteChangeRequest(rackFaceRequest, "Autodesk:CustomCommand:RackFaceChgDef", m_application.ActiveDocument);
		}

		public override void StopCommand()
		{
			//implement this command specific functionality
			TerminatePreviewGraphics();

			//destroy the command dialog
			m_rackFaceCmdDlg.Hide();
			m_rackFaceCmdDlg.Dispose();
			m_rackFaceCmdDlg = null;	

			//call base command button's StopCommand (to disconnect interaction sinks)
			base.StopCommand();
		}

		public override void EnableInteraction()
		{
			//call base command button's Enable Interaction 
			base.EnableInteraction();

			//implement this command specific functionality
			//clear selection filter
			m_selectEvents.ClearSelectionFilter();

			//reset selections
			m_selectEvents.ResetSelections();

			//specify selection filter and cursor
			if(m_rackFaceCmdDlg.checkBoxFace.Checked)
			{
				if(m_rackEdge != null)
				{
					m_selectEvents.AddToSelectedEntities(m_rackEdge);
				}

				//set the selection filter to a planar face
				m_selectEvents.AddSelectionFilter(SelectionFilterEnum.kPartFacePlanarFilter);

				//set a cursor to specify face selection
				m_interactionEvents.SetCursor(CursorTypeEnum.kCursorBuiltInCrosshair,null,null);

				//set the status bar message
				m_interactionEvents.StatusBarText = "Select a planar face with at least one linear edge";
			}
			else
			{
				if(m_rackFace != null)
				{
					m_selectEvents.AddToSelectedEntities(m_rackFace);
				}
				
				//set the selection filter to a linear edge
				m_selectEvents.AddSelectionFilter(SelectionFilterEnum.kPartEdgeLinearFilter);

				//set a cursor to specify edge selection
				m_interactionEvents.SetCursor(CursorTypeEnum.kCursorBuiltInArrowCursor,null,null);

				//set the status bar message
				m_interactionEvents.StatusBarText = "Select a linear edge on the selected face";
			}
		}

		public override void DisableInteraction()
		{
			//call base command button's Disable Interaction 
			base.DisableInteraction();

			//implement this command specific functionality
			//set the default cursor to notify that selection is not active
			m_interactionEvents.SetCursor(CursorTypeEnum.kCursorBuiltInArrow,null,null);
		}

		//-----------------------------------------------------------------------------
		//----- Implementation of Callbacks
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//----- Implementation of SelectEvents callbacks
		//-----------------------------------------------------------------------------
		
		public override void OnPreSelect(object preSelectEntity, out bool doHighlight, ObjectCollection morePreSelectEntities, SelectionDeviceEnum selectionDevice, Point modelPosition, Point2d viewPosition, View view)
		{
			doHighlight = false;

			//if rack face is being pre-selected, if edge has been selected already
			//highlight the face only if the already selected edge belongs to the face
			if (preSelectEntity is Face)
			{
				if (m_rackEdge != null)
				{
					Face preSelectFace = (Face)preSelectEntity;

					Edges edges = preSelectFace.Edges;

					int noEdges = edges.Count;

					for(int edgeCt = 1; edgeCt <= noEdges; edgeCt++)
					{
						Edge edge = edges[edgeCt];

						if (edge == m_rackEdge)
						{
							doHighlight = true;
							break;
						}				
					}
				}
				else
				{
					doHighlight = true;
				}
			}

			//if rack edge is being pre-selected, if face has been selected already
			//highlight the edge only if the edge belongs to the already selected face
			if (preSelectEntity is Edge)
			{
				if (m_rackFace != null)
				{
					Edge preSelectEdge = (Edge)preSelectEntity;

					Edges edges = m_rackFace.Edges;

					int noEdges = edges.Count;

					for(int edgeCt = 1; edgeCt <= noEdges; edgeCt++)
					{
						Edge edge = edges[edgeCt];

						if (edge == preSelectEdge)
						{
							doHighlight = true;
							break;
						}				
					}
				}
				else
				{
					doHighlight = true;
				}
			}
		}

		public override void OnSelect (ObjectsEnumerator justSelectedEntities, SelectionDeviceEnum selectionDevice, Point modelPosition, Point2d viewPosition, View view)
		{
			int noSelectedEntities = justSelectedEntities.Count;

			if (noSelectedEntities > 0) 
			{
				object selectedEntity = justSelectedEntities[1];

				//if face is selected
				if ((m_rackFaceCmdDlg.checkBoxFace.Checked) && (selectedEntity is Face))
				{
					//get the selected face, if face had been previously selected, set it to NULL
					m_rackFace = (Face)selectedEntity;

					//un-check rack face selection button
					m_rackFaceCmdDlg.checkBoxFace.Checked = false;

					//if edge has not been selected, start selection for it
					if(m_rackEdge == null)
					{
						//check rack direction selection button
						m_rackFaceCmdDlg.checkBoxDirection.Checked = true;

						//start direction selection
						EnableInteraction();
					}
					else
					{
						//disable selection
						DisableInteraction();

						UpdateCommandStatus();
					}
				}

				//if edge is selected
				if ((m_rackFaceCmdDlg.checkBoxDirection.Checked) && (selectedEntity is Edge))
				{
					//get the selected edge, if edge had been previously selected, set it to NULL
					m_rackEdge = (Edge)selectedEntity;

					//un-check rack direction selection button
					m_rackFaceCmdDlg.checkBoxDirection.Checked = false;

					//disable selection
					DisableInteraction();

					UpdateCommandStatus();
				}
			}	
		}

		//-----------------------------------------------------------------------------
		//----- Implementation of InteractionEvents callbacks
		//-----------------------------------------------------------------------------

		public override void OnHelp(EventTimingEnum beforeOrAfter, NameValueMap context, out HandlingCodeEnum handlingCode)
		{
			//get the help manager object and display the start page of the "Inventor API" help
			m_application.HelpManager.DisplayHelpTopic("ADMAPI_12_0.chm", "");
			handlingCode = HandlingCodeEnum.kEventHandled;
		}

		//-----------------------------------------------------------------------------
		//----- End of Callbacks
		//-----------------------------------------------------------------------------

		public void UpdateCommandStatus()
		{
			//get the rack parameters from the rack command dialog 

			//by default, disable the OK button on dialog
			//enable it later if all parameters are valid
			m_rackFaceCmdDlg.buttonOK.Enabled = false;

			//all parameters must be valid
			if (!m_rackFaceCmdDlg.AllParametersAreValid())
			{
				return;
			}

			//transfer parameters
			m_noTeeth = int.Parse(m_rackFaceCmdDlg.m_noTeeth);
			
			m_rackHeight = GetValueFromExpression(m_rackFaceCmdDlg.m_rackHeight);
			
			m_rackWidth = GetValueFromExpression(m_rackFaceCmdDlg.m_rackWidth);

			m_rackExtents = GetValueFromExpression(m_rackFaceCmdDlg.m_rackExtents);

			switch (m_rackFaceCmdDlg.m_rackExtentsDirection)
			{
				case 0:
					m_rackFeatureExtentDirection = PartFeatureExtentDirectionEnum.kNegativeExtentDirection;
					break;
				case 1:
					m_rackFeatureExtentDirection = PartFeatureExtentDirectionEnum.kPositiveExtentDirection;
					break;
				case 2:
					m_rackFeatureExtentDirection = PartFeatureExtentDirectionEnum.kSymmetricExtentDirection;
					break;
			}

			//if all rack face parameters are alright, update the preview graphics and enable "OK" button
			if (m_rackFace != null && m_rackEdge != null && m_noTeeth > 0 && m_rackHeight > 0 && m_rackWidth > 0 && m_rackExtents > 0)
			{
				//update the preview
				UpdatePreviewGraphics();

				//enable the OK button on dialog
				m_rackFaceCmdDlg.buttonOK.Enabled = true;
			}
		}

		public double GetValueFromExpression(string expression)
		{
			double value = 0.0;

			//get the active document
			Document activeDocument = m_application.ActiveDocument;

			//get the units of measure object
			UnitsOfMeasure unitsOfMeasure = activeDocument.UnitsOfMeasure;

			//get the current length units of the user
			UnitsTypeEnum lengthUnitsType = unitsOfMeasure.LengthUnits;

			//convert the expression to the current length units of user
            try
            {
                object vVal;
                vVal = unitsOfMeasure.GetValueFromExpression(expression, lengthUnitsType);
                value = System.Convert.ToDouble(vVal);
            }
            catch (System.Exception e)
            {
                string strErrorMsg = e.Message;

                value = 0.0;
                return value;
            }

			return value;
		}

		//-----------------------------------------------------------------------------
		//----- Implementation of CRackFaceCmd Preview Graphics
		//-----------------------------------------------------------------------------

		void InitializePreviewGraphics()
		{
			InteractionGraphics interactionGraphics = m_interactionEvents.InteractionGraphics;

			ClientGraphics previewClientGraphics = interactionGraphics.PreviewClientGraphics;

			m_previewClientGraphicsNode = previewClientGraphics.AddNode(1);

			m_triangleStripGraphics = m_previewClientGraphicsNode.AddTriangleStripGraphics();

			GraphicsDataSets graphicsDataSets = interactionGraphics.GraphicsDataSets;

			m_graphicsCoordinateSet = graphicsDataSets.CreateCoordinateSet(1);

			m_graphicsColorSet = graphicsDataSets.CreateColorSet(1);

			m_graphicsColorSet.Add(1, 100, 100, 200);
			m_graphicsColorSet.Add(2, 150, 150, 250);

			m_graphicsColorIndexSet = graphicsDataSets.CreateIndexSet(1);

			m_triangleStripGraphics.CoordinateSet = m_graphicsCoordinateSet;

			m_triangleStripGraphics.ColorSet = m_graphicsColorSet;

			m_triangleStripGraphics.ColorIndexSet = m_graphicsColorIndexSet;

			m_triangleStripGraphics.ColorBinding = ColorBindingEnum.kPerItemColors;
			m_triangleStripGraphics.DepthPriority = 4;
			m_triangleStripGraphics.BurnThrough = true;
		}

		void UpdatePreviewGraphics()
		{
			//remove the existing co-ordinates			
			m_graphicsCoordinateSet = null;
			
			InteractionGraphics interactionGraphics = m_interactionEvents.InteractionGraphics;
			GraphicsDataSets graphicsDataSets = interactionGraphics.GraphicsDataSets;

			m_graphicsCoordinateSet = graphicsDataSets.CreateCoordinateSet(1);
			
			//remove the existing color indices
			m_graphicsColorIndexSet = null;
			
			m_graphicsColorIndexSet = graphicsDataSets.CreateIndexSet(1);
			m_triangleStripGraphics.CoordinateSet = m_graphicsCoordinateSet;
			m_triangleStripGraphics.ColorIndexSet = m_graphicsColorIndexSet;

			TransientGeometry transientGeometry = m_application.TransientGeometry;

			//get rack edge start point and end point
			Vertex rackEdgeStartVertex = m_rackEdge.StartVertex;

            Point rackEdgeStartPt = rackEdgeStartVertex.Point;

            Vertex rackEdgeStopVertex = m_rackEdge.StopVertex;

            Point rackEdgeStopPt = rackEdgeStopVertex.Point;

            double rackEdgeStartPtX = rackEdgeStartPt.X;
            double rackEdgeStartPtY = rackEdgeStartPt.Y;
            double rackEdgeStartPtZ = rackEdgeStartPt.Z;

            double rackEdgeStopPtX = rackEdgeStopPt.X;
            double rackEdgeStopPtY = rackEdgeStopPt.Y;
            double rackEdgeStopPtZ = rackEdgeStopPt.Z;

            double rackEdgeLengthX = rackEdgeStopPtX - rackEdgeStartPtX;
            double rackEdgeLengthY = rackEdgeStopPtY - rackEdgeStartPtY;
            double rackEdgeLengthZ = rackEdgeStopPtZ - rackEdgeStartPtZ;

            Vector rackEdgeVector = transientGeometry.CreateVector(rackEdgeLengthX, rackEdgeLengthY, rackEdgeLengthZ);

            object rackFaceGeometry = m_rackFace.Geometry;

            Plane rackFacePlane = (Plane)rackFaceGeometry;	

			UnitVector rackFaceNormalUnitVector = rackFacePlane.Normal;

			double rackFaceNormalX = rackFaceNormalUnitVector.X;
			double rackFaceNormalY = rackFaceNormalUnitVector.Y;
			double rackFaceNormalZ = rackFaceNormalUnitVector.Z;

			Vector rackFaceNormalVector = rackFaceNormalUnitVector.AsVector();

			Vector rackPositiveExtentDirectionVector = rackEdgeVector.CrossProduct(rackFaceNormalVector);

			UnitVector rackPositiveExtentDirectionUnitVector = rackPositiveExtentDirectionVector.AsUnitVector();

			double rackPositiveExtentDirectionX = rackPositiveExtentDirectionUnitVector.X;
			double rackPositiveExtentDirectionY = rackPositiveExtentDirectionUnitVector.Y;
			double rackPositiveExtentDirectionZ = rackPositiveExtentDirectionUnitVector.Z;

			Point graphicsEdgeStartPt = null;
			Point graphicsParallelEdgeStartPt = null;

			switch (m_rackFeatureExtentDirection)
			{
				case PartFeatureExtentDirectionEnum.kNegativeExtentDirection:
					
					graphicsEdgeStartPt = rackEdgeStartPt;

					graphicsParallelEdgeStartPt = transientGeometry.CreatePoint(rackEdgeStartPtX - m_rackExtents * rackPositiveExtentDirectionX,
						rackEdgeStartPtY - m_rackExtents * rackPositiveExtentDirectionY,
						rackEdgeStartPtZ - m_rackExtents * rackPositiveExtentDirectionZ);
					break;

				case PartFeatureExtentDirectionEnum.kPositiveExtentDirection:

					graphicsEdgeStartPt = rackEdgeStartPt;

					graphicsParallelEdgeStartPt = transientGeometry.CreatePoint(rackEdgeStartPtX + m_rackExtents * rackPositiveExtentDirectionX,
						rackEdgeStartPtY + m_rackExtents * rackPositiveExtentDirectionY,
						rackEdgeStartPtZ + m_rackExtents * rackPositiveExtentDirectionZ);
					break;

				case PartFeatureExtentDirectionEnum.kSymmetricExtentDirection:

					graphicsEdgeStartPt = transientGeometry.CreatePoint(rackEdgeStartPtX - m_rackExtents * rackPositiveExtentDirectionX,
						rackEdgeStartPtY - m_rackExtents * rackPositiveExtentDirectionY,
						rackEdgeStartPtZ - m_rackExtents * rackPositiveExtentDirectionZ);

					graphicsParallelEdgeStartPt = transientGeometry.CreatePoint(rackEdgeStartPtX + m_rackExtents * rackPositiveExtentDirectionX,
						rackEdgeStartPtY + m_rackExtents * rackPositiveExtentDirectionY,
						rackEdgeStartPtZ + m_rackExtents * rackPositiveExtentDirectionZ);
					break;
			}

			double graphicsEdgeStartPtX = graphicsEdgeStartPt.X;
			double graphicsEdgeStartPtY = graphicsEdgeStartPt.Y;
			double graphicsEdgeStartPtZ = graphicsEdgeStartPt.Z;
			
			double graphicsParallelEdgeStartPtX = graphicsParallelEdgeStartPt.X;
			double graphicsParallelEdgeStartPtY = graphicsParallelEdgeStartPt.Y;
			double graphicsParallelEdgeStartPtZ = graphicsParallelEdgeStartPt.Z;

			//get the rack parallel edge start point and end point
			double rackEdgeLength = rackEdgeStartPt.DistanceTo(rackEdgeStopPt);

			double nonRackWidth = rackEdgeLength - m_rackWidth;

			double toothWidthProportion = 0.35;

			double toothMajorWidth = m_rackWidth  / (m_noTeeth + (m_noTeeth - 1) * toothWidthProportion);

			double toothMinorWidth = toothWidthProportion * toothMajorWidth;

			double toothSlopeWidth = (toothMajorWidth - toothMinorWidth) / 2.0;

			Point point1,point2,point3,point4;
			point1 = transientGeometry.CreatePoint(graphicsEdgeStartPtX + (((nonRackWidth / 2) / rackEdgeLength) * rackEdgeLengthX),
				graphicsEdgeStartPtY + (((nonRackWidth / 2) / rackEdgeLength) * rackEdgeLengthY),
				graphicsEdgeStartPtZ + (((nonRackWidth / 2) / rackEdgeLength) * rackEdgeLengthZ));

			point3 = transientGeometry.CreatePoint(graphicsParallelEdgeStartPtX + (((nonRackWidth / 2) / rackEdgeLength) * rackEdgeLengthX),
				graphicsParallelEdgeStartPtY + (((nonRackWidth / 2) / rackEdgeLength) * rackEdgeLengthY),
				graphicsParallelEdgeStartPtZ + (((nonRackWidth / 2) / rackEdgeLength) * rackEdgeLengthZ));

            AddGraphicsPoints(point1, point3);

			double Xnr = rackFaceNormalX * m_rackHeight;
			double Ynr = rackFaceNormalY * m_rackHeight;
			double Znr = rackFaceNormalZ * m_rackHeight;

			double Xintv = toothSlopeWidth * rackEdgeLengthX / rackEdgeLength;
			double Yintv = toothSlopeWidth * rackEdgeLengthY / rackEdgeLength;
			double Zintv = toothSlopeWidth * rackEdgeLengthZ / rackEdgeLength;

			double Xsht = toothMinorWidth * rackEdgeLengthX / rackEdgeLength;
			double Ysht = toothMinorWidth * rackEdgeLengthY / rackEdgeLength;
			double Zsht = toothMinorWidth * rackEdgeLengthZ / rackEdgeLength;

			for (int toothCt = 1; toothCt <= m_noTeeth; toothCt++)
			{
				double point1X = point1.X;
				double point1Y = point1.Y;
				double point1Z = point1.Z;

				double point3X = point3.X;
				double point3Y = point3.Y;
				double point3Z = point3.Z;

				point2 = transientGeometry.CreatePoint(point1X + Xintv - Xnr, point1Y + Yintv - Ynr, point1Z + Zintv - Znr);
				point4 = transientGeometry.CreatePoint(point3X + Xintv - Xnr, point3Y + Yintv - Ynr, point3Z + Zintv - Znr);

                AddGraphicsPoints(point2, point4);
				AddColorIndex(1);

				point1 = null; 
				point3 = null;

				double point2X = point2.X;
				double point2Y = point2.Y;
				double point2Z = point2.Z;

				double point4X = point4.X;
				double point4Y = point4.Y;
				double point4Z = point4.Z;

				point1 = transientGeometry.CreatePoint(point2X + Xsht, point2Y + Ysht, point2Z + Zsht);
				point3 = transientGeometry.CreatePoint(point4X + Xsht, point4Y + Ysht, point4Z + Zsht);

                AddGraphicsPoints(point1, point3);
				AddColorIndex(2);

				point2 = null;
				point4 = null;

				point1X = point1.X;
				point1Y = point1.Y;
				point1Z = point1.Z;
				
				point3X = point3.X;
				point3Y = point3.Y;
				point3Z = point3.Z;

				point2 = transientGeometry.CreatePoint(point1X + Xintv + Xnr, point1Y + Yintv + Ynr, point1Z + Zintv + Znr);
				point4 = transientGeometry.CreatePoint(point3X + Xintv + Xnr, point3Y + Yintv + Ynr, point3Z + Zintv + Znr);

                AddGraphicsPoints(point2, point4);
				AddColorIndex(1);

				point1 = null; 
				point3 = null;

				point2X = point2.X;
				point2Y = point2.Y;
				point2Z = point2.Z;

				point4X = point4.X;
				point4Y = point4.Y;
				point4Z = point4.Z;

				point1 = transientGeometry.CreatePoint(point2X + Xsht, point2Y + Ysht, point2Z + Zsht);
				point3 = transientGeometry.CreatePoint(point4X + Xsht, point4Y + Ysht, point4Z + Zsht);

				if (toothCt != m_noTeeth)
				{
                    AddGraphicsPoints(point1, point3);
					AddColorIndex(2);

					point2 = null;
					point4 = null;
				}
			}

			m_application.ActiveView.Update();
		}

		void AddGraphicsPoints(Point cornerPt1, Point cornerPt2)
		{
			int noGraphicsCoordPts = m_graphicsCoordinateSet.Count;

			m_graphicsCoordinateSet.Add(noGraphicsCoordPts + 1, cornerPt1);
			m_graphicsCoordinateSet.Add(noGraphicsCoordPts + 2, cornerPt2);
		}

		void AddColorIndex(int colorIndex)
		{
			int noGraphicsColorIndices = m_graphicsColorIndexSet.Count;

			m_graphicsColorIndexSet.Add(noGraphicsColorIndices + 1, colorIndex);
			m_graphicsColorIndexSet.Add(noGraphicsColorIndices + 2, colorIndex);
		}

		void TerminatePreviewGraphics()
		{
			m_graphicsCoordinateSet.Delete();

			m_graphicsColorSet.Delete();

			m_graphicsColorIndexSet.Delete();

			m_triangleStripGraphics.Delete();

			m_previewClientGraphicsNode.Delete();

			m_graphicsCoordinateSet = null;
			m_graphicsColorSet = null;
			m_graphicsColorIndexSet = null;
			m_triangleStripGraphics = null;
			m_previewClientGraphicsNode = null;	
		}
	}
}